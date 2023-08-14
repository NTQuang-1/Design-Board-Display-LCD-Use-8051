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
						delay_ms(1000);
			break;
		case 2:
						lcd_init();
						for(i=16;i>=-1;i--){
							lcd_gotoxy(1,i);
							lcd_str_cp(marks);
							lcd_gotoxy(2,15-i);
							lcd_str_cp(name);
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
							delay_ms(300);
							lcd_cmd(lcd_clear);
						}
			break;
		default: break;
	}
}

void main(){
	
	while(1){
		lcd_cmd(lcd_clear);
		led_display(1);
		led_display(2);
		lcd_effect(2);
	}
}