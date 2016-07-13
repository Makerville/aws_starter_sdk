/*
 *  Copyright (C) 2008-2016, Marvell International Ltd.
 *  All Rights Reserved.
 */

#include <wmstdio.h>
#include <wm_os.h>
#include <mdev_gpio.h>
#include <mdev_pinmux.h>
#include <board.h>



/*------------------Global Variable Definitions ---------*/

struct pinHeaders{
	unsigned int gpio;
	unsigned int mux;
};

struct pinHeaders h1[11],h2[14];

/* Configure GPIO pins to be used as LED and push button */
static void configure_gpios()
{
	mdev_t *pinmux_dev, *gpio_dev;
	int i;
	/* Initialize  pinmux driver */
	pinmux_drv_init();

	/* Open pinmux driver */
	pinmux_dev = pinmux_drv_open("MDEV_PINMUX");

	/* Initialize GPIO driver */
	gpio_drv_init();

	/* Open GPIO driver */
	gpio_dev = gpio_drv_open("MDEV_GPIO");

	for (i=0;i<11;i++){
		/* Configure GPIO pin function for GPIO connected to LED */
		pinmux_drv_setfunc(pinmux_dev, h1[i].gpio, h1[i].mux);
		/* Configure GPIO pin direction as Output */
		gpio_drv_setdir(gpio_dev, h1[i].gpio, GPIO_OUTPUT);
		/* Keep initial state of LED: ON */
		gpio_drv_write(gpio_dev, h1[i].gpio, 1);
	}

	for (i=0;i<14;i++){
		/* Configure GPIO pin function for GPIO connected to LED */
		pinmux_drv_setfunc(pinmux_dev, h2[i].gpio, h2[i].mux);
		/* Configure GPIO pin direction as Output */
		gpio_drv_setdir(gpio_dev, h2[i].gpio, GPIO_OUTPUT);
		/* Keep initial state of LED: ON */
		gpio_drv_write(gpio_dev, h2[i].gpio, 1);
	}

	/* Close drivers */
	pinmux_drv_close(pinmux_dev);
	gpio_drv_close(gpio_dev);
}

int main(void)
{
	int ret = 0,i;
		/* Initializes console on UART0 */
		ret = wmstdio_init(UART0_ID, 0);
		if (ret == -WM_FAIL) {
			wmprintf("Failed to initialize console on uart0\r\n");
			return -1;
		}

		wmprintf(" Test the pins on Knit\r\n");

	// Header 1 i.e. the one on the left
	h1[0].gpio 	= GPIO_6;
	h1[0].mux 	= PINMUX_FUNCTION_1;
	h1[1].gpio 	= GPIO_9;
	h1[1].mux 	= PINMUX_FUNCTION_1;
	h1[2].gpio 	=	GPIO_10;
	h1[2].mux		=	PINMUX_FUNCTION_1;
	h1[3].gpio 	=	GPIO_7;
	h1[3].mux		=	PINMUX_FUNCTION_1;
	h1[4].gpio 	=	GPIO_8;
	h1[4].mux		=	PINMUX_FUNCTION_1;
	h1[5].gpio	=	GPIO_25;
	h1[5].mux		=	PINMUX_FUNCTION_1;
	h1[6].gpio	=	GPIO_26;
	h1[6].mux		=	PINMUX_FUNCTION_1;
	h1[7].gpio 	= GPIO_23;
	h1[7].mux		= PINMUX_FUNCTION_1;
	h1[8].gpio	=	GPIO_22;
	h1[8].mux		=	PINMUX_FUNCTION_1;
	h1[9].gpio	=	GPIO_3;
	h1[9].mux		=	PINMUX_FUNCTION_0;
	h1[10].gpio	=	GPIO_2;
	h1[10].mux	=	PINMUX_FUNCTION_0;

	// Header 2 i.e. the one on the right
	h2[0].gpio 	= GPIO_4;
	h2[0].mux 	= PINMUX_FUNCTION_0;
	h2[1].gpio 	= GPIO_5;
	h2[1].mux 	= PINMUX_FUNCTION_0;
	h2[2].gpio 	=	GPIO_0;
	h2[2].mux		=	PINMUX_FUNCTION_0;
	h2[3].gpio 	=	GPIO_1;
	h2[3].mux		=	PINMUX_FUNCTION_0;
	h2[4].gpio 	=	GPIO_49;
	h2[4].mux		=	PINMUX_FUNCTION_0;
	h2[5].gpio	=	GPIO_48;
	h2[5].mux		=	PINMUX_FUNCTION_0;
	h2[6].gpio	=	GPIO_47;
	h2[6].mux		=	PINMUX_FUNCTION_0;
	h2[7].gpio 	= GPIO_46;
	h2[7].mux		= PINMUX_FUNCTION_0;
	h2[8].gpio	=	GPIO_43;
	h2[8].mux		=	PINMUX_FUNCTION_0;
	h2[9].gpio	=	GPIO_42;
	h2[9].mux		=	PINMUX_FUNCTION_0;
	h2[10].gpio	=	GPIO_41;
	h2[10].mux	=	PINMUX_FUNCTION_0;
	h2[11].gpio	=	GPIO_24;
	h2[11].mux	=	PINMUX_FUNCTION_1;
	h2[12].gpio	=	GPIO_39;
	h2[12].mux	=	PINMUX_FUNCTION_0;
	h2[13].gpio	=	GPIO_40;
	h2[13].mux	=	PINMUX_FUNCTION_0;

	configure_gpios();

	while (1){
		for(i=0;i<11;i++){
				mdev_t *gpio_dev = gpio_drv_open("MDEV_GPIO");
				gpio_drv_write(gpio_dev, h1[i].gpio, 0);
				os_thread_sleep(os_msec_to_ticks(100));
				gpio_drv_write(gpio_dev, h1[i].gpio, 1);
				gpio_drv_close(gpio_dev);

		}
		for(i=0;i<14;i++){
			mdev_t *gpio_dev = gpio_drv_open("MDEV_GPIO");
			gpio_drv_write(gpio_dev, h2[i].gpio, 0);
			os_thread_sleep(os_msec_to_ticks(100));
			gpio_drv_write(gpio_dev, h2[i].gpio, 1);
			gpio_drv_close(gpio_dev);

		}
	};
	return 0;
}
