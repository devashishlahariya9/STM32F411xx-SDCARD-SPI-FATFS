#include <string.h>
#include <ff.h>

char* data = "A Microcontroller (MCU for microcontroller unit) is a small computer on a single metal-oxide-semiconductor (MOS) integrated circuit (IC) chip. A microcontroller contains one or more CPUs (processor cores) along with memory and programmable input/output peripherals. Program memory in the form of ferroelectric RAM, NOR flash or OTP ROM is also often included on chip, as well as a small amount of RAM. Microcontrollers are designed for embedded applications, in contrast to the microprocessors used in personal computers or other general purpose applications consisting of various discrete chips. In modern terminology, a microcontroller is similar to, but less sophisticated than, a system on a chip (SoC). An SoC may include a microcontroller as one of its components, but usually integrates it with advanced peripherals like a graphics processing unit (GPU), a Wi-Fi module, or one or more coprocessors. Microcontrollers are used in automatically controlled products and devices, such as automobile engine control systems, implantable medical devices, remote controls, office machines, appliances, power tools, toys and other embedded systems. By reducing the size and cost compared to a design that uses a separate microprocessor, memory, and input/output devices, microcontrollers make it economical to digitally control even more devices and processes. Mixed signal microcontrollers are common, integrating analog components needed to control non-digital electronic systems. In the context of the internet of things, microcontrollers are an economical and popular means of data collection, sensing and actuating the physical world as edge devices.";

int main(void)
{
	__attribute__((unused))FRESULT fr;
	FATFS fs;
	FIL fil;

	f_mount(&fs, "", 0);

	fr = f_open(&fil, "Hello.txt", FA_WRITE | FA_OPEN_ALWAYS);

	f_printf(&fil, data);

	f_close(&fil);

	while(1)
	{

	}
	return 0;
}
