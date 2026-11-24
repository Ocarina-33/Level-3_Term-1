// UNCOMMENT ONE OF THE FOLLOWING TWO LINES DEPENDING ON YOUR MATRIX POLARITY
#define MATRIX_COMMON_ROW_ANODE 1
// #define MATRIX_COMMON_ROW_CATHODE 1

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

typedef uint8_t bool;

#define FALSE 0x00
#define TRUE 0xFF
#define UP -1
#define DOWN 1
#define LEFT -1
#define RIGHT 1
#define PRESS_CONF 6
#define START_SPEED 25  // Change this number to adjust game speed (higher = slower, lower = faster)

typedef enum { O, I, L, J, S, Z,  T } shape_type;
	
void ADC_Init()
{
	ADCSRA = 0b10000001;		/* Enable ADC, fr/128  */
	ADMUX =  0b01000000;		/* Vref: Avcc, ADC channel: 0 */
}

int ADC_Read(char channel)
{
	int ADC_value;
	
	ADMUX = (0x40) | (channel & 0x07);/* set input channel to read */
	ADCSRA |= (1<<ADSC);	/* start conversion */
	while((ADCSRA &(1<<ADIF))== 0);	/* monitor end of conversion interrupt flag */
	
	ADCSRA |= (1<<ADIF);	/* clear interrupt flag */
	ADC_value = (int)ADCL;	/* read lower byte */
	ADC_value = ADC_value + (int)ADCH*256;/* read higher 2 bits, Multiply with weightage */

	return ADC_value;		/* return digital value */
}

volatile char row[] = {128, 64, 32, 16, 8, 4, 2, 1};

volatile bool shape_O_array[4][4]={{FALSE,  TRUE,  TRUE, FALSE},
{FALSE,  TRUE,  TRUE, FALSE},
{FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE}};

volatile bool shape_I_array[4][4]={{FALSE,  TRUE, FALSE, FALSE},
{FALSE,  TRUE, FALSE, FALSE},
{FALSE,  TRUE, FALSE, FALSE},
{FALSE,  TRUE, FALSE, FALSE}};

volatile bool shape_L_array[4][4]={{FALSE,  TRUE, FALSE, FALSE},
{FALSE,  TRUE, FALSE, FALSE},
{FALSE,  TRUE,  TRUE, FALSE},
{FALSE, FALSE, FALSE, FALSE}};

volatile bool shape_J_array[4][4]={{FALSE, FALSE,  TRUE, FALSE},
{FALSE, FALSE,  TRUE, FALSE},
{FALSE,  TRUE,  TRUE, FALSE},
{FALSE, FALSE, FALSE, FALSE}};

volatile bool shape_S_array[4][4]={{FALSE,  TRUE,  TRUE, FALSE},
{ TRUE,  TRUE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE}};

volatile bool shape_Z_array[4][4]={{ TRUE,  TRUE, FALSE, FALSE},
{FALSE,  TRUE,  TRUE, FALSE},
{FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE}};

volatile bool shape_T_array[4][4]={{ TRUE,  TRUE,  TRUE, FALSE},
{FALSE,  TRUE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE}};

volatile bool current_display[16][8]={{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE}};
	
bool play[16][8]=
{{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE},
{FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE},
{FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE},
{FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE}};

bool temp_shape_array[4][4];
bool current_shape_array[4][4];
volatile int current_R = 0;
volatile int current_C = 2;
int current_shape = -1;
int next_shape = 0;
int count_speed = START_SPEED;
int count_count = 0;

void UART_init(void){
	int UBBRValue = 25;//AS described before setting baud rate
	UBRRH = (unsigned char) (UBBRValue >> 8);
	UBRRL = (unsigned char) UBBRValue;
	UCSRB = (1<<RXEN) |(1 << TXEN);
	UCSRC = (1 << USBS) | (3 << UCSZ0);
	
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 8; j++){
			current_display[i][j] = FALSE;
		}
	}
	count_speed = START_SPEED;
}

void UART_send(unsigned char data){
	while ((UCSRA & (1<<UDRE)) == 0x00);
	UDR = data; 
	_delay_ms(4);
}

void row_shift(int length, bool shape_array[][4], int direction, int shift_count)
{
	for(int counter=0; counter<shift_count; counter++){
		int index = 0;
		if (direction>0){
			index = length-1;
		}

		for (int i=0; i<length-1; i++){
			for (int j=0; j<length; j++){
				shape_array[index][j] = shape_array[index-direction][j];
			}
			index = index - direction;
		}
		for (int j=0; j<length; j++){
			shape_array[index][j] = FALSE;
		}
	}
}

void col_shift(int length, bool shape_array[][4], int direction, int shift_count)
{
	for(int counter=0; counter<shift_count; counter++){
		int index = 0;
		if (direction>0){
			index = length-1;
		}

		for (int j=0; j<length-1; j++){
			for (int i=0; i<length; i++){
				shape_array[i][index] = shape_array[i][index-direction];
			}
			index = index - direction;
		}
		for (int i=0; i<length; i++){
			shape_array[i][index] = FALSE;
		}
	}
}

void align_top_left_justify(bool shape_array[][4])
{
	int shift_count = -1;
	int shift_direction = UP;
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			if(shape_array[i][j] == TRUE){
				shift_count = i;
				break;
			}
		}
		if (shift_count != -1){
			break;
		}
	}
	row_shift(4, shape_array,shift_direction,shift_count);
	
	int width = 0;
	int w1 = -1, w2 = -1;
	for (int j=0; j<4; j++){
		for (int i=0; i<4; i++){
			if(shape_array[i][j] == TRUE){
				if(w1 == -1){
					w1 = j;
				}
				w2 = j;
				break;
			}
		}
		if((w1 != -1) && (w2<j)){
			break;
		}
	}
	width = w2 - w1 + 1;
	if(width == 1 || width == 2){
		shift_count = w1 - 1;
	}
	else if(width == 3 || width == 4){
		shift_count = w1 - 0;
	}
	if(shift_count<0){
		shift_count = -shift_count;
		shift_direction = RIGHT;
	}
	else{
		shift_direction = LEFT;
	}
	col_shift(4,shape_array,shift_direction,shift_count);
}

void rotate_shape(bool shape_array[][4])
{
	bool temp[4][4];
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			temp[i][j] = shape_array[i][j];	
		}
	}
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			temp_shape_array[i][j] = temp[j][i];
		}
	}
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			temp[i][j] = temp_shape_array[i][j];
		}
	}
	for (int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			temp_shape_array[i][j] = temp[i][3-j];
		}
	}
	align_top_left_justify(temp_shape_array);
}

bool check_valid(int row, int col, bool shape_array[][4])
{
	for(int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			if(shape_array[i][j] == TRUE){
				if((row+i) > 15){
					return FALSE;
				}
				if((col+j) < 0 || (col+j) > 7){
					return FALSE;
				}
				if(current_display[row+i][col+j] == TRUE){
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}

void set_shape(bool shape_array[][4])
{
	for(int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			if(shape_array[i][j] == TRUE){
				current_display[current_R+i][current_C+j] = shape_array[i][j];
			}
		}
	}
}

void remove_shape(bool shape_array[][4])
{
	for(int i=0; i<4; i++){
		for (int j=0; j<4; j++){
			if(shape_array[i][j] == TRUE){
				current_display[current_R+i][current_C+j] = FALSE;
			}
		}
	}
}

int get_col(int row)
{
	int col_value = 0x00;
	for (int j=0; j<8; j++){
		if(current_display[row][j] == TRUE){
			col_value |= 1<<(j);
		}
	}
	return col_value;
}

void remove_row(int row){
	for(int i = row ; i > 0 ; i--){
		for(int j = 0 ; j< 8; j++){
			current_display[i][j] = current_display[i-1][j];
		}
	}
	for(int i = 0 ; i < 8; i++){
		current_display[0][i] = FALSE;
	}
}

void update_score1x(){
	uint8_t temp ;
	for(int i = 0 ; i < 16 ; i++){
		temp = TRUE;
		for(int j = 0 ; j < 8; j++){
			temp &= current_display[i][j];
		}
		if(temp == TRUE){
			UART_send(10);
			PORTA &= ~(1 << PA2);
			_delay_ms(200);
			PORTA |= (1 << PA2);
			_delay_ms(200);
			remove_row(i);
		}
	}
}

void update_score2x(){
	uint8_t temp ;
	for(int i = 0 ; i < 13 ; i++){
		temp = TRUE;
		int ii = i;
		for(int t = 0; t < 4; t++){
			for(int j = 0 ; j < 8; j++){
				temp &= current_display[ii][j];
			}
			ii++;
		}
		if(temp == TRUE){
			UART_send(11);
			PORTA &= ~(1 << PA2);
			_delay_ms(200);
			PORTA |= (1 << PA2);
			_delay_ms(200);
			for(int t = 0; t < 4; t++){
				remove_row(i+3);
			}
		}
	}
}

void go_left(){
	remove_shape(current_shape_array);
	if(check_valid(current_R, current_C-1 , current_shape_array) == TRUE){
		current_C--;
	}
	set_shape(current_shape_array);
}

void go_right(){
	remove_shape(current_shape_array);
	if(check_valid(current_R, current_C+1 , current_shape_array) == TRUE){
		current_C++;
	}
	set_shape(current_shape_array);
}

void go_down(){
	remove_shape(current_shape_array);
	if(check_valid(current_R+1, current_C , current_shape_array) == TRUE){
		current_R++;
		set_shape(current_shape_array);
	}
	else{
		set_shape(current_shape_array);
		current_C = 2;
		current_R = 0;
		for(int i = 0 ; i < 4; i++){
			for(int j = 0; j < 4; j++){
				current_shape_array[i][j] = FALSE;
			}
		}
		current_shape = -1;
		update_score2x();
		update_score1x();
	}
}

void generate_shape(){
	int shape = rand()%7;
	current_shape = next_shape;
	next_shape = shape;
	shape = current_shape;
	
	if(shape == 0){
		for(int i = 0 ; i < 4; i++){
			for(int j = 0; j < 4; j++){
				current_shape_array[i][j] = shape_O_array[i][j];
			}
		}
	}
	else if(shape == 1){
		for(int i = 0 ; i < 4; i++){
			for(int j = 0; j < 4; j++){
				current_shape_array[i][j] = shape_I_array[i][j];
			}
		}
	}
	else if(shape == 2){
		for(int i = 0 ; i < 4; i++){
			for(int j = 0; j < 4; j++){
				current_shape_array[i][j] = shape_L_array[i][j];
			}
		}
	}
	else if(shape == 3){
		for(int i = 0 ; i < 4; i++){
			for(int j = 0; j < 4; j++){
				current_shape_array[i][j] = shape_J_array[i][j];
			}
		}
	}
	else if(shape == 4){
		for(int i = 0 ; i < 4; i++){
			for(int j = 0; j < 4; j++){
				current_shape_array[i][j] = shape_S_array[i][j];
			}
		}
	}
	else if(shape == 5){
		for(int i = 0 ; i < 4; i++){
			for(int j = 0; j < 4; j++){
				current_shape_array[i][j] = shape_Z_array[i][j];
			}
		}
	}
	else if(shape == 6){
		for(int i = 0 ; i < 4; i++){
			for(int j = 0; j < 4; j++){
				current_shape_array[i][j] = shape_T_array[i][j];
			}
		}
	}
}

void start_again(){
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 8; j++){
			current_display[i][j] = FALSE;
		}
	}
	count_speed = START_SPEED;
	count_count = 0;
	current_shape = -1;
	current_R = 0;
	current_C = 2;
	next_shape = rand() % 7;
	PORTD |= 0xF0; // Turn off matrix rows to prevent freezing flash
	PORTC |= 0xF0;
	PORTA &= ~(1 << PA2);
			_delay_ms(200);
			PORTA |= (1 << PA2);
			_delay_ms(200);
}

void display(int i){
	uint8_t led_col = 0x00;
#ifdef MATRIX_COMMON_ROW_ANODE
	PORTC = 0x00; // common row connection
	PORTC |= row[i]; // common row connection
	PORTB = ~get_col(i); // upper matrix column
	// lower matrix column
	led_col = ~get_col(i+8);
	PORTA |= 0xF0; // clear
	PORTD |= 0xF0; //clear
	PORTA &= ((led_col & 0x0F) << 4) | 0x0F; // col0-col3 --> A4-A7
	PORTD &= (led_col & 0xF0) | 0x0F; // col4- col7 --> D4-D7
	_delay_ms(2);
	PORTB = ~0x0; // upper matrix column
	PORTA |= 0xF0;
	PORTD |= 0xF0;
#else
	PORTC = 0xFF;             
	PORTC &= ~row[i];         
	
	PORTB = get_col(i); 
	led_col = get_col(i+8);
	
	PORTA &= 0x0F; 
	PORTD &= 0x0F; 
	
	PORTA |= (led_col & 0x0F) << 4; 
	PORTD |= (led_col & 0xF0);      
	
	_delay_ms(2);
	
	PORTB = 0x00; 
	PORTA &= 0x0F;
	PORTD &= 0x0F;
#endif
}

void new_game(){
	int ADC_Value_X = -1;
	for(int i = 0 ;i < 16 ; i++){
		for(int j = 0; j < 8; j++){
			current_display[i][j] = play[i][j];
		}
	}
	int i = 7;
	unsigned int seed_counter = 0;
	
	while(1){
		display(i);
		
		if(i == 7) {
			i = 0;
		}
		else {
			i++;
		}
		
		seed_counter++; 
		
		// Check Joystick
		ADC_Value_X = ADC_Read(0);
		if(ADC_Value_X < 100){
			srand(seed_counter); 
			start_again();
			UART_send(7);
			return;
		}
		// Check Restart Button
		if ((PIND & (1 << PD2)) == 0) { _delay_ms(50); if ((PIND & (1 << PD2)) == 0) { srand(seed_counter); start_again(); UART_send(7); return; } }
	}
}

void new_piece(){
	while (current_shape == -1){
		current_R = 0;
		current_C = 2;
		generate_shape();
		if(check_valid(0 , 2 , current_shape_array) == TRUE){
			UART_send(next_shape);
			set_shape(current_shape_array);
		}
		else{
			UART_send(9);
			start_again();
			new_game();
			_delay_ms(200);
			UART_send(8);
		}
	}
}

int get_leftmost_col(bool shape_array[][4]) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (shape_array[i][j] == TRUE) return j;
        }
    }
    return 0;
}

int pressed_confidence_level = 0;

void movement(){
	int ADC_Value_Y = ADC_Read(1);
	int ADC_Value_X = ADC_Read(0);
	
	if(ADC_Value_Y < 100){
		pressed_confidence_level++;
		if(pressed_confidence_level > PRESS_CONF){
			go_right();
			pressed_confidence_level = 0;
		}
	}
	else if(ADC_Value_Y > 900){
		pressed_confidence_level++;
		if(pressed_confidence_level > PRESS_CONF){
			go_left();
			pressed_confidence_level = 0;
		}
	}
	else if(ADC_Value_X > 900){
		pressed_confidence_level++;
		if(pressed_confidence_level > PRESS_CONF){
			go_down();
			pressed_confidence_level = 0;
		}
	}
	else if(ADC_Value_X < 100){
		pressed_confidence_level++;
		if(pressed_confidence_level > PRESS_CONF+2){
			rotate_shape(current_shape_array);
			remove_shape(current_shape_array);
			
			int min_j_before = get_leftmost_col(current_shape_array);
			int min_j_after = get_leftmost_col(temp_shape_array);
			int target_C = current_C + min_j_before - min_j_after;
			
			bool rotated = FALSE;
			
			if(check_valid(current_R, target_C, temp_shape_array) == TRUE){
				current_C = target_C;
				rotated = TRUE;
			}
			else if(check_valid(current_R, current_C, temp_shape_array) == TRUE){
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
			
			pressed_confidence_level = 0;
		}
	}
    else {
        pressed_confidence_level = 0;
    }
}

void mcu_init(){
	MCUCSR |= 1<<JTD;
	MCUCSR |= 1<<JTD;
	DDRA = 0b11111100;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	PORTA |= (1 << PA2); // Set HIGH to turn OFF active-low buzzer 
	
	// Joystick click button (SW) initialization
	DDRD &= ~(1 << PD2); // Set PD2 (Pin 16) as input
	PORTD |= (1 << PD2); // Enable internal pull-up resistor
}

int main(void)
{
	srand(1); 
	mcu_init();
	int i = 7, count = 0;
	count_speed = START_SPEED; 
	count_count = 0;
	ADC_Init();
	UART_init();
	new_game();
	
	while (1)
	{
		display(i);
		
		if(i == 7) {
			i = 0;
			
						// Safe Reset Button: Ignores if Joystick is pushed UP (< 200)
			if ((PIND & (1 << PD2)) == 0) { 
				if (ADC_Read(0) > 200) { 
					_delay_ms(50); 
					if ((PIND & (1 << PD2)) == 0) { 
						start_again(); 
						UART_send(8); 
						new_game(); 
					} 
				}
			}
			
			new_piece();
			movement();
			
			count++;
			if(count >= count_speed){
				go_down();
				count_count++;
				count = 0;
				if(count_count > 5){
					if(count_speed > 10){
						count_speed --;
					}
					count_count = 0;
				}
			}
		}
		else {
			i++;
		}
	}
}

