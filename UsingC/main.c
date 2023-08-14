#include <REGX52.H>
#include <LCD.H>

void lcd_effect (int choice){
	char name[20] = " NGUYEN THANH QUANG";
	char marks[10] = " DIEM 10";
	int i,j=0;
	switch (choice) {
		case 1:
						lcd_init();
						lcd_gotoxy(1,1);
						lcd_str_cp(marks);
						lcd_gotoxy(2,1);
						lcd_str_cp(name);
						delay_ms(500);
			break;
		case 2:
						lcd_init();
						for(i=16;i>=-1;i--){
							lcd_gotoxy(1,i);
							lcd_str_cp(marks);
							lcd_gotoxy(2,15-i);
							lcd_str_cp(name);
							if(i%2 == 0){
								led_display(light_Even);
							}else {
								led_display(light_Odd);
							}
							delay_ms(300);
							lcd_cmd(lcd_clear);
						}
			break;
		case 3:
						lcd_init();
						for(i=16;i>=-1;i--){
							lcd_gotoxy(1,17-i);
							lcd_str_cp(marks);
							lcd_gotoxy(2,i);
							lcd_str_cp(name);
							if(i%2 == 0){
								led_display(light_Even);
							}else {
								led_display(light_Odd);
							}
							delay_ms(300);
							lcd_cmd(lcd_clear);
						}
			break;
		default: break;
	}
}

void main(){
	led_display(1);
	delay_ms(500);
	led_display(2);
	delay_ms(500);
	while(1){
		lcd_effect(2);
	}
}