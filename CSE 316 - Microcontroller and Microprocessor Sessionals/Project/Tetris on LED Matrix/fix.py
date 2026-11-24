import re

with open('ATmega2_main.c', 'r') as f:
    content = f.read()

# Add global var at the top after includes
content = content.replace('#include "i2c_lcd.h"', '#include "i2c_lcd.h"\n\nbool playing_screen_drawn = false;')

# Update show_start_screen
content = content.replace('void show_start_screen() {', 'void show_start_screen() {\n    playing_screen_drawn = false;')

# Update show_game_over_screen
content = content.replace('void show_game_over_screen() {', 'void show_game_over_screen() {\n    playing_screen_drawn = false;')

# Replace show_playing_screen exactly
old_func = '''void show_playing_screen() {
    char score_msg[] = " Score:         "; 
    char score_str[10];
    itoa(score_update, score_str, 10);
    
    int i = 0;
    while(score_str[i] != '\\0' && i < 3) {
        score_msg[8 + i] = score_str[i];
        i++;
    }
    
    char second_msg[] = " Next piece :   ";
    second_msg[14] = ch1;
    
    lcd_set_cursor(1,0);
    lcd_write_string(score_msg);
    lcd_set_cursor(2,0);
    lcd_write_string(second_msg);
}'''

new_func = '''void show_playing_screen() {
    if (!playing_screen_drawn) {
        lcd_clear();
        lcd_set_cursor(1,0);
        lcd_write_string(" Score:         ");
        lcd_set_cursor(2,0);
        lcd_write_string(" Next piece :   ");
        playing_screen_drawn = true;
    }
    
    char score_str[10];
    itoa(score_update, score_str, 10);
    
    char pad[4] = "   ";
    int i = 0;
    while(score_str[i] != '\\0' && i < 3) {
        pad[i] = score_str[i];
        i++;
    }
    
    lcd_set_cursor(1, 8);
    lcd_write_string(pad);
    
    lcd_set_cursor(2, 14);
    char next_str[2] = {ch1, '\\0'};
    lcd_write_string(next_str);
}'''

content = content.replace(old_func, new_func)

with open('ATmega2_main.c', 'w') as f:
    f.write(content)
