#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "i2c_lcd.h"

#define DIN_PIN PB0
#define CS_PIN  PB1
#define CLK_PIN PB2

int score_update = 0;
int flag = 2; 
char ch1 = '-'; 

const uint8_t shape_O_array[8] = {0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00};
const uint8_t shape_I_array[8] = {0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00};
const uint8_t shape_L_array[8] = {0x00, 0x00, 0x10, 0x10, 0x18, 0x00, 0x00, 0x00};
const uint8_t shape_J_array[8] = {0x00, 0x00, 0x08, 0x08, 0x18, 0x00, 0x00, 0x00};
const uint8_t shape_S_array[8] = {0x00, 0x00, 0x00, 0x0C, 0x18, 0x00, 0x00, 0x00};
const uint8_t shape_Z_array[8] = {0x00, 0x00, 0x00, 0x18, 0x0C, 0x00, 0x00, 0x00};
const uint8_t shape_T_array[8] = {0x00, 0x00, 0x00, 0x1C, 0x08, 0x00, 0x00, 0x00};

void MAX7219_write(uint8_t address, uint8_t data) {
    PORTB &= ~(1 << CS_PIN);
    for (int i = 7; i >= 0; i--) {
        PORTB &= ~(1 << CLK_PIN);
        if (address & (1 << i)) PORTB |= (1 << DIN_PIN);
        else PORTB &= ~(1 << DIN_PIN);
        PORTB |= (1 << CLK_PIN);
    }
    for (int i = 7; i >= 0; i--) {
        PORTB &= ~(1 << CLK_PIN);
        if (data & (1 << i)) PORTB |= (1 << DIN_PIN);
        else PORTB &= ~(1 << DIN_PIN);
        PORTB |= (1 << CLK_PIN);
    }
    PORTB |= (1 << CS_PIN);
}

void MAX7219_clear() {
    for (int i = 1; i <= 8; i++) {
        MAX7219_write(i, 0x00);
    }
}

void MAX7219_init() {
    DDRB |= (1 << DIN_PIN) | (1 << CS_PIN) | (1 << CLK_PIN);
    PORTB |= (1 << CS_PIN);
    _delay_ms(10);
    MAX7219_write(0x09, 0x00); 
    MAX7219_write(0x0A, 0x03); 
    MAX7219_write(0x0B, 0x07); 
    MAX7219_write(0x0C, 0x01); 
    
    // Diagnostic flash 
    MAX7219_write(0x0F, 0x01); 
    _delay_ms(500);
    MAX7219_write(0x0F, 0x00); 
    
    MAX7219_clear();
}

void UART_init(void) {
    int UBRR_Value = 25; 
    UBRRH = (unsigned char) (UBRR_Value >> 8);
    UBRRL = (unsigned char) UBRR_Value;
    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << USBS) | (3 << UCSZ0);
}

unsigned char UART_receive(void) {
    while ((UCSRA & (1<<RXC)) == 0x00);
    return UDR;
}

void show_start_screen() {
    lcd_clear();
    char msg1[] = "Press up for    ";
    char msg2[] = "starting game   ";
    lcd_set_cursor(1,0);
    lcd_write_string(msg1);
    lcd_set_cursor(2,0);
    lcd_write_string(msg2);
    
    MAX7219_clear();
}

void show_game_over_screen() {
    lcd_clear();
    char score_msg[] = "Final Score:    ";
    char score_str[10];
    itoa(score_update, score_str, 10);
    
    int i = 0;
    while(score_str[i] != '\0' && i < 3) {
        score_msg[13 + i] = score_str[i];
        i++;
    }
    
    char msg2[] = "   Game Over!   ";
    lcd_set_cursor(1,0);
    lcd_write_string(score_msg);
    lcd_set_cursor(2,0);
    lcd_write_string(msg2);
}

void show_playing_screen() {
    char score_msg[] = " Score:         "; 
    char score_str[10];
    itoa(score_update, score_str, 10);
    
    int i = 0;
    while(score_str[i] != '\0' && i < 3) {
        score_msg[8 + i] = score_str[i];
        i++;
    }
    
    char second_msg[] = " Next piece :   ";
    second_msg[14] = ch1;
    
    lcd_set_cursor(1,0);
    lcd_write_string(score_msg);
    lcd_set_cursor(2,0);
    lcd_write_string(second_msg);
}

void draw_shape(int ch) {
    const uint8_t* shape_ptr = 0;
    if(ch == 0)      { shape_ptr = shape_O_array; ch1 = 'O'; }
    else if(ch == 1) { shape_ptr = shape_I_array; ch1 = 'I'; }
    else if(ch == 2) { shape_ptr = shape_L_array; ch1 = 'L'; }
    else if(ch == 3) { shape_ptr = shape_J_array; ch1 = 'J'; }
    else if(ch == 4) { shape_ptr = shape_S_array; ch1 = 'S'; }
    else if(ch == 5) { shape_ptr = shape_Z_array; ch1 = 'Z'; }
    else if(ch == 6) { shape_ptr = shape_T_array; ch1 = 'T'; }
    else return;

    for (int i = 0; i < 8; i++) {
        MAX7219_write(i + 1, shape_ptr[i]);
    }
    
    if (flag == 1) show_playing_screen();
}

int main(void) {
    _delay_ms(500); 
    MCUCSR |= 1<<JTD;
    MCUCSR |= 1<<JTD;
    
    DDRD = 0b11111110; 
    DDRC = 0xFC; // Leave PC0 and PC1 as inputs for I2C
    
    UART_init();
    MAX7219_init(); 
    lcd_init();     // Initialize new I2C LCD
    
    score_update = 0;
    flag = 2; 
    show_start_screen();

    while (1) {
        int ch = UART_receive();
        
        if (ch == 10) {
            score_update++;
            if (flag == 1) show_playing_screen();
        }
        else if (ch == 11) {
            score_update += 8;
            if (flag == 1) show_playing_screen();
        }
        else if (ch == 9) { 
            flag = 0;
            show_game_over_screen();
            MAX7219_clear();
            _delay_ms(3000);
            score_update = 0;
            flag = 2; 
            show_start_screen();
        }
        else if (ch == 8) { 
            flag = 2;
            score_update = 0;
            show_start_screen();
        }
        else if (ch == 7) { 
            flag = 1;
            score_update = 0;
            show_playing_screen();
            MAX7219_clear();
            
            ch = UART_receive();
            draw_shape(ch);
        }
        else if (ch >= 0 && ch <= 6) { 
            if (flag == 1) {
                draw_shape(ch);
            }
        }
    }
}



