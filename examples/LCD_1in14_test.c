#include "EPD_Test.h"
#include "LCD_1in14.h"

/* set address */
bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int LCD_1in14_test(void)
{
    DEV_Delay_ms(100);
    printf("LCD_1in14_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }
    DEV_SET_PWM(50);
    /* LCD Init */
    printf("1.14inch LCD demo...\r\n");
    LCD_1IN14_Init(HORIZONTAL);
    LCD_1IN14_Clear(WHITE);

    int frame = 0;
    
    //LCD_SetBacklight(1023);
    UDOUBLE Imagesize = LCD_1IN14_HEIGHT*LCD_1IN14_WIDTH*2;
    UWORD *BlackImage;
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage((UBYTE *)BlackImage,LCD_1IN14.WIDTH,LCD_1IN14.HEIGHT, 0, WHITE);
    Paint_SetScale(65);
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(WHITE);

    // /*2.Drawing on the image*/
    uint8_t keyA = 15; 
    uint8_t keyB = 17; 

    uint8_t up = 2;
	uint8_t dowm = 18;
	uint8_t left = 16;
	uint8_t right = 20;
	uint8_t ctrl = 3;
   

    SET_Infrared_PIN(keyA);    
    SET_Infrared_PIN(keyB);
		 
	SET_Infrared_PIN(up);
    SET_Infrared_PIN(dowm);
    SET_Infrared_PIN(left);
    SET_Infrared_PIN(right);
    SET_Infrared_PIN(ctrl);
    
    Paint_Clear(WHITE);
    Paint_DrawRectangle(208,12,229,32, 0xF800, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
    Paint_DrawRectangle(208,103,229,123, 0xF800, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
    Paint_DrawRectangle(37,35,58,55, 0xF800, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
    Paint_DrawRectangle(37,85,58,105, 0xF800, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
    Paint_DrawRectangle(12,60,33,80, 0xF800, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
    Paint_DrawRectangle(62,60,83,80, 0xF800, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
    Paint_DrawRectangle(37,60,58,80, 0xF800, DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
    LCD_1IN14_Display(BlackImage);
    
    
    while(1){
        frame += 1;

        Paint_DrawImage(gImage_1inch14_1,frame,0,240,135);

        if(DEV_Digital_Read(keyA ) == 0){
            Paint_DrawRectangle(208,12,228,32, 0xF800, DOT_PIXEL_2X2,DRAW_FILL_FULL);
            printf("gpio =%d\r\n",keyA);
        }
        else{
            Paint_DrawRectangle(208,12,228,32, WHITE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
        }
            
        if(DEV_Digital_Read(keyB ) == 0){
            Paint_DrawRectangle(208,103,228,123, 0xF800, DOT_PIXEL_2X2,DRAW_FILL_FULL);
            printf("gpio =%d\r\n",keyB);
        }
        else{
            Paint_DrawRectangle(208,103,228,123, WHITE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
        }
        
        if(DEV_Digital_Read(up ) == 0){
            Paint_DrawRectangle(37,35,57,55, 0xF800, DOT_PIXEL_2X2,DRAW_FILL_FULL);
            printf("gpio =%d\r\n",up);
        }
        else{
            Paint_DrawRectangle(37,35,57,55, WHITE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
        }

        if(DEV_Digital_Read(dowm ) == 0){
            Paint_DrawRectangle(37,85,57,105, 0xF800, DOT_PIXEL_2X2,DRAW_FILL_FULL);
            printf("gpio =%d\r\n",dowm);
        }
        else{
            Paint_DrawRectangle(37,85,57,105, WHITE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
        }
        
        if(DEV_Digital_Read(left ) == 0){
            Paint_DrawRectangle(12,60,32,80, 0xF800, DOT_PIXEL_2X2,DRAW_FILL_FULL);
            printf("gpio =%d\r\n",left);
        }
        else{
            Paint_DrawRectangle(12,60,32,80, WHITE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
        }
            
        if(DEV_Digital_Read(right ) == 0){
            Paint_DrawRectangle(62,60,82,80, 0xF800, DOT_PIXEL_2X2,DRAW_FILL_FULL);
            printf("gpio =%d\r\n",right);
        }
        else{
            Paint_DrawRectangle(62,60,82,80, WHITE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
        }
        
        if(DEV_Digital_Read(ctrl ) == 0){
            Paint_DrawRectangle(37,60,57,80, 0xF800, DOT_PIXEL_2X2,DRAW_FILL_FULL);
            printf("gpio =%d\r\n",ctrl);
        }
        else{
            Paint_DrawRectangle(37,60,57,80, WHITE, DOT_PIXEL_2X2,DRAW_FILL_FULL);
        }

        LCD_1IN14_DisplayWindows(0,0,240,135,BlackImage);
    }

    /* Module Exit */
    free(BlackImage);
    BlackImage = NULL;
    
    DEV_Module_Exit();
    return 0;
}
