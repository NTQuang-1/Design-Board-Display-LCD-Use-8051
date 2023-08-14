#include <REGX52.H>
#include <LCD.H>

void delay_ms(int ms){
	TMOD = 0x01;
	while(ms--){
		TH0 = 0xFC;
		TL0 = 0x18;
		TR0 = 1;
		while(!TF0);
		TR0 = 0;
		TF0 = 0;
	}
	TMOD &= 0x00;
}

void led_display(int choice){ 
	switch (choice){
		case light_Odd:
						led_name_N1 = 0;
						led_name_T  = 1;
						led_name_Q  = 0;
						led_name_U  = 1;
						led_name_A  = 0;
						led_name_N2 = 1;
						led_name_G  = 0;
						delay_ms(500);
		break;
		case light_Even:
						led_name_N1 = 1;
						led_name_T  = 0;
						led_name_Q  = 1;
						led_name_U  = 0;
						led_name_A  = 1;
						led_name_N2 = 0;
						led_name_G  = 1;
						delay_ms(500);
		break;
		default: break;
	}			
}
void lcd_init(){
	lcd_cmd(lcd_clear);
	lcd_cmd(lcd_5x7);
	lcd_cmd(lcd_display_screen_and_turnOff_ptr);
}

void lcd_cmd(unsigned char cmd){
	lcd_data = cmd;
	lcd_rs   = 0;
	lcd_en   = 1;
	lcd_en   = 0;
	cmd <= 0x02 ? delay_ms(2):delay_ms(1);
}

void lcd_chr_cp (char c){
	lcd_rs   = 1;
	lcd_data = c;
	lcd_en   = 0;
	lcd_en   = 1;
	c <= 0x02 ? delay_ms(2):delay_ms(1);
}

void lcd_str_cp(char *str){
	unsigned char i = 0;
	while(str[i]!=0){
		lcd_chr_cp(str[i]);
		i++;
	}
}

void lcd_gotoxy(int rows,int col){
	int result;
	col -= 1;
	if(rows == 1){
		result = 0x80 + col;
	}
	if(rows == 2){
		result = 0xC0 + col;
	}
	lcd_cmd(result);
}