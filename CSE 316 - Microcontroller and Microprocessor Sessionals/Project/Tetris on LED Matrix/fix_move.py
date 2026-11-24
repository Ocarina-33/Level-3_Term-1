import re

with open('ATmega1_main.c', 'r') as f:
    content = f.read()

pattern = r"int pressed_confidence_level = 0;.*?void mcu_init\(\)\{"

new_move = '''int pressed_confidence_x = 0;
int pressed_confidence_y = 0;

void movement(){
	int ADC_Value_Y = ADC_Read(1);
	int ADC_Value_X = ADC_Read(0);
	
	if(ADC_Value_Y < 100){
		pressed_confidence_y++;
		if(pressed_confidence_y > PRESS_CONF){
			go_right();
			pressed_confidence_y = 0;
		}
	}
	else if(ADC_Value_Y > 900){
		pressed_confidence_y++;
		if(pressed_confidence_y > PRESS_CONF){
			go_left();
			pressed_confidence_y = 0;
		}
	}
    else {
        pressed_confidence_y = 0;
    }
	
	if(ADC_Value_X > 900){
		pressed_confidence_x++;
		if(pressed_confidence_x > PRESS_CONF){
			go_down();
			pressed_confidence_x = 0;
		}
	}
	else if(ADC_Value_X < 100){
		pressed_confidence_x++;
		if(pressed_confidence_x > PRESS_CONF+2){
			rotate_shape(current_shape_array);
			remove_shape(current_shape_array);
			
			bool rotated = FALSE;
			if(check_valid(current_R, current_C, temp_shape_array) == TRUE){
				rotated = TRUE;
			}
			else if(check_valid(current_R, current_C + 1, temp_shape_array) == TRUE){
				current_C++;
				rotated = TRUE;
			}
			else if(check_valid(current_R, current_C + 2, temp_shape_array) == TRUE){
				current_C += 2;
				rotated = TRUE;
			}
			else if(check_valid(current_R, current_C - 1, temp_shape_array) == TRUE){
				current_C--;
				rotated = TRUE;
			}
			else if(check_valid(current_R, current_C - 2, temp_shape_array) == TRUE){
				current_C -= 2;
				rotated = TRUE;
			}
			
			if(rotated){
				for(int i = 0 ; i < 4; i++){
					for(int j = 0; j < 4; j++){
						current_shape_array[i][j] = temp_shape_array[i][j];
					}
				}
			}
			set_shape(current_shape_array);
			
			pressed_confidence_x = 0;
		}
	}
    else {
        pressed_confidence_x = 0;
    }
}

void mcu_init(){'''

content = re.sub(pattern, new_move, content, flags=re.DOTALL)

with open('ATmega1_main.c', 'w') as f:
    f.write(content)
