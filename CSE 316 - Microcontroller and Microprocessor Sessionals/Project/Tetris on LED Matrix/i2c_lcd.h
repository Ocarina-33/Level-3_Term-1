#ifndef I2C_LCD_H
#define I2C_LCD_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

// Let's completely bypass PC0/PC1 and use PORTB!
#define SCL_PIN PB3
#define SDA_PIN PB4

uint8_t lcd_addr = 0x00;
bool lcd_connected = true;

void I2C_Init() {
    // Software I2C needs no hardware init
}

void I2C_delay() {
    _delay_us(15); 
}

void SDA_HIGH() {
    DDRB &= ~(1 << SDA_PIN);  
    PORTB &= ~(1 << SDA_PIN); 
}

void SDA_LOW() {
    PORTB &= ~(1 << SDA_PIN); 
    DDRB |= (1 << SDA_PIN);   
}

void SCL_HIGH() {
    DDRB &= ~(1 << SCL_PIN); 
    PORTB &= ~(1 << SCL_PIN); 
}

void SCL_LOW() {
    PORTB &= ~(1 << SCL_PIN); 
    DDRB |= (1 << SCL_PIN);   
}

void I2C_Start() {
    SDA_HIGH();
    SCL_HIGH();
    I2C_delay();
    SDA_LOW();
    I2C_delay();
    SCL_LOW();
    I2C_delay();
}

void I2C_Stop() {
    SDA_LOW();
    I2C_delay();
    SCL_HIGH();
    I2C_delay();
    SDA_HIGH();
    I2C_delay();
}

bool I2C_Write_Check(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        if (data & 0x80) SDA_HIGH();
        else SDA_LOW();
        data <<= 1;
        
        I2C_delay();
        SCL_HIGH();
        I2C_delay();
        SCL_LOW();
        I2C_delay();
    }
    
    // Read ACK
    SDA_HIGH(); 
    I2C_delay();
    SCL_HIGH();
    I2C_delay();
    bool ack = !(PINB & (1 << SDA_PIN)); // 1 if ACK received (pulled low)
    SCL_LOW();
    I2C_delay();
    return ack;
}

void lcd_scan_address() {
    lcd_addr = 0x00;
    for (uint8_t a = 0x20; a <= 0x3F; a++) {
        I2C_Start();
        bool ack = I2C_Write_Check(a << 1);
        I2C_Stop();
        if (ack) {
            lcd_addr = a;
            lcd_connected = true;
            return;
        }
        _delay_ms(2);
    }
    lcd_connected = false;
}

void lcd_send_nibble(char nibble) {
    if (!lcd_connected) return;
    char data_u = nibble & 0xF0;
    I2C_Start();
    I2C_Write_Check(lcd_addr << 1);
    I2C_Write_Check(data_u | 0x0C); 
    I2C_Write_Check(data_u | 0x08); 
    I2C_Stop();
}

void lcd_send_cmd (char cmd) {
    if (!lcd_connected) return;
    char data_u = (cmd&0xf0); 
    char data_l = ((cmd<<4)&0xf0); 
    I2C_Start();
    I2C_Write_Check(lcd_addr << 1);
    I2C_Write_Check(data_u | 0x0C);  
    I2C_Write_Check(data_u | 0x08);  
    I2C_Write_Check(data_l | 0x0C);  
    I2C_Write_Check(data_l | 0x08);  
    I2C_Stop();
}

void lcd_send_data (char data) {
    if (!lcd_connected) return;
    char data_u = (data&0xf0);
    char data_l = ((data<<4)&0xf0);
    I2C_Start();
    I2C_Write_Check(lcd_addr << 1);
    I2C_Write_Check(data_u | 0x0D);  
    I2C_Write_Check(data_u | 0x09);  
    I2C_Write_Check(data_l | 0x0D);  
    I2C_Write_Check(data_l | 0x09);  
    I2C_Stop();
}

void lcd_init (void) {
    _delay_ms(100); 
    lcd_scan_address();
    
    if (!lcd_connected) return;

    lcd_send_nibble(0x30);
    _delay_ms(5);
    lcd_send_nibble(0x30);
    _delay_us(150);
    lcd_send_nibble(0x30);
    _delay_ms(10);
    lcd_send_nibble(0x20); 
    _delay_ms(10);

    lcd_send_cmd(0x28); 
    _delay_ms(1);
    lcd_send_cmd(0x0C); 
    _delay_ms(1);
    lcd_send_cmd(0x01); 
    _delay_ms(2);
    lcd_send_cmd(0x06); 
    _delay_ms(1);
}

void lcd_clear(void) {
    lcd_send_cmd(0x01);
    _delay_ms(2);
}

void lcd_set_cursor(int row, int col) {
    switch (row) {
        case 1:
            lcd_send_cmd(0x80 + col);
            break;
        case 2:
            lcd_send_cmd(0xC0 + col);
            break;
    }
}

void lcd_write_string(char *str) {
    while (*str) {
        lcd_send_data(*str++);
    }
}

#endif
