#define lcd_data P1
#define lcd_rs P2_0
#define lcd_en P2_1

#define light_Odd 1
#define light_Even 2
#define led_name_N1 P3_0
#define led_name_T P3_1
#define led_name_Q P3_2
#define led_name_U P3_3
#define led_name_A P3_4
#define led_name_N2 P3_5
#define led_name_G P3_6

enum code_cmd {
	lcd_clear = 0x01,
	lcd_5x7   = 0x38,
	lcd_display_screen_and_turnOff_ptr = 0x0C
};
void delay_ms(int);
void led_display(int);
void lcd_init();
void lcd_cmd(unsigned char);
void lcd_chr_cp (char);
void lcd_str_cp(char*);
void lcd_gotoxy(int,int);