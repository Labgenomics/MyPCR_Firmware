# MPLAB IDE generated this makefile for use with GNU make.
# Project: PeltierPCR.mcp
# Date: Fri Aug 17 18:35:17 2012

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

./OUTPUT/PeltierPCR.cof : OBJECTS/main.o OBJECTS/usb_device.o OBJECTS/usb_function_hid.o OBJECTS/usb_descriptors.o OBJECTS/Init.o OBJECTS/PCR_Task.o OBJECTS/Timer.o OBJECTS/Delay.o OBJECTS/GlobalTypeVars.o OBJECTS/Temp_Ctrl.o OBJECTS/Temp_Sensor.o OBJECTS/Temp_Table.o OBJECTS/State.o OBJECTS/Pragma.o OBJECTS/Usb_Task.o
	$(LD) /l"C:\Embedded\MCC18\lib" "rm18f4550 - HID Bootload.lkr" "OBJECTS\main.o" "OBJECTS\usb_device.o" "OBJECTS\usb_function_hid.o" "OBJECTS\usb_descriptors.o" "OBJECTS\Init.o" "OBJECTS\PCR_Task.o" "OBJECTS\Timer.o" "OBJECTS\Delay.o" "OBJECTS\GlobalTypeVars.o" "OBJECTS\Temp_Ctrl.o" "OBJECTS\Temp_Sensor.o" "OBJECTS\Temp_Table.o" "OBJECTS\State.o" "OBJECTS\Pragma.o" "OBJECTS\Usb_Task.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"./OUTPUT\PeltierPCR.cof" /M"./OUTPUT\PeltierPCR.map" /W

OBJECTS/main.o : main.c ../../MCC18/h/stdio.h ../../MCC18/h/stdlib.h ../../MCC18/h/string.h USB/usb_common.h USB/usb_device.h CONFIG/BootLoader.h main.c HardwareProfile.h HardwareProfile\ -\ PICDEM\ FSUSB.h PCR/Timer.h USB/usb.h CONFIG/Compiler.h ../../MCC18/h/p18cxxx.h ../../MCC18/h/p18f4550.h ../../MCC18/h/stdarg.h ../../MCC18/h/stddef.h DEFINE/GenericTypeDefs.h USB/usb_config.h ../../MCC18/h/limits.h USB/usb_ch9.h USB/usb_hal.h USB/usb_hal_pic18.h CONFIG/Init.h
	$(CC) -p=18F4550 /i"C:\Embedded\MCC18\h" "main.c" -fo="./OBJECTS\main.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

OBJECTS/usb_device.o : USB/usb_device.c ../../MCC18/h/stdio.h ../../MCC18/h/stdlib.h ../../MCC18/h/string.h USB/usb_common.h USB/usb_device.h USB/usb_device.c DEFINE/GenericTypeDefs.h ../../MCC18/h/stddef.h CONFIG/Compiler.h ../../MCC18/h/p18cxxx.h ../../MCC18/h/p18f4550.h ../../MCC18/h/stdarg.h USB/USB.h USB/usb_config.h ../../MCC18/h/limits.h USB/usb_ch9.h USB/usb_hal.h USB/usb_hal_pic18.h HardwareProfile.h HardwareProfile\ -\ PICDEM\ FSUSB.h
	$(CC) -p=18F4550 /i"C:\Embedded\MCC18\h" "USB\usb_device.c" -fo="./OBJECTS\usb_device.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

OBJECTS/usb_function_hid.o : USB/usb_function_hid.c ../../MCC18/h/stdio.h ../../MCC18/h/stdlib.h ../../MCC18/h/string.h USB/usb_common.h USB/usb_device.h USB/usb_function_hid.c DEFINE/GenericTypeDefs.h ../../MCC18/h/stddef.h CONFIG/Compiler.h ../../MCC18/h/p18cxxx.h ../../MCC18/h/p18f4550.h ../../MCC18/h/stdarg.h USB/usb.h USB/usb_config.h ../../MCC18/h/limits.h USB/usb_ch9.h USB/usb_hal.h USB/usb_hal_pic18.h USB/usb_function_hid.h
	$(CC) -p=18F4550 /i"C:\Embedded\MCC18\h" "USB\usb_function_hid.c" -fo="./OBJECTS\usb_function_hid.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

OBJECTS/usb_descriptors.o : USB/usb_descriptors.c ../../MCC18/h/stdio.h ../../MCC18/h/stdlib.h ../../MCC18/h/string.h USB/usb_common.h USB/usb_device.h USB/usb_descriptors.c USB/usb.h CONFIG/Compiler.h ../../MCC18/h/p18cxxx.h ../../MCC18/h/p18f4550.h ../../MCC18/h/stdarg.h ../../MCC18/h/stddef.h DEFINE/GenericTypeDefs.h USB/usb_config.h ../../MCC18/h/limits.h USB/usb_ch9.h USB/usb_hal.h USB/usb_hal_pic18.h USB/usb_function_hid.h
	$(CC) -p=18F4550 /i"C:\Embedded\MCC18\h" "USB\usb_descriptors.c" -fo="./OBJECTS\usb_descriptors.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

OBJECTS/Init.o : CONFIG/Init.c ../../MCC18/h/stdio.h ../../MCC18/h/stdlib.h ../../MCC18/h/string.h USB/usb_common.h USB/usb_device.h TOOLS/Delay.h PCR/PCR_Task.h CONFIG/Init.c HardwareProfile.h HardwareProfile\ -\ PICDEM\ FSUSB.h CONFIG/Init.h CONFIG/Compiler.h ../../MCC18/h/p18cxxx.h ../../MCC18/h/p18f4550.h ../../MCC18/h/stdarg.h ../../MCC18/h/stddef.h DEFINE/UserDefs.h DEFINE/GenericTypeDefs.h PCR/Timer.h USB/usb.h USB/usb_config.h ../../MCC18/h/limits.h USB/usb_ch9.h USB/usb_hal.h USB/usb_hal_pic18.h DEFINE/GlobalTypeVars.h
	$(CC) -p=18F4550 /i"C:\Embedded\MCC18\h" "CONFIG\Init.c" -fo="./OBJECTS\Init.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

OBJECTS/PCR_Task.o : PCR/PCR_Task.c PCR/PCR_Task.h ../../MCC18/h/string.h ../../MCC18/h/stdio.h ../../MCC18/h/stdlib.h PCR/Temp_Ctrl.h PCR/PCR_Task.c DEFINE/GlobalTypeVars.h DEFINE/GenericTypeDefs.h ../../MCC18/h/stddef.h DEFINE/UserDefs.h HardwareProfile.h HardwareProfile\ -\ PICDEM\ FSUSB.h CONFIG/Compiler.h ../../MCC18/h/p18cxxx.h ../../MCC18/h/p18f4550.h ../../MCC18/h/stdarg.h PCR/State.h
	$(CC) -p=18F4550 /i"C:\Embedded\MCC18\h" "PCR\PCR_Task.c" -fo="./OBJECTS\PCR_Task.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

OBJECTS/Timer.o : PCR/Timer.c ../../MCC18/h/stdio.h ../../MCC18/h/stdlib.h ../../MCC18/h/string.h PCR/Timer.c CONFIG/Compiler.h ../../MCC18/h/p18cxxx.h ../../MCC18/h/p18f4550.h ../../MCC18/h/stdarg.h ../../MCC18/h/stddef.h HardwareProfile.h HardwareProfile\ -\ PICDEM\ FSUSB.h DEFINE/GenericTypeDefs.h DEFINE/GlobalTypeVars.h DEFINE/UserDefs.h PCR/Timer.h
	$(CC) -p=18F4550 /i"C:\Embedded\MCC18\h" "PCR\Timer.c" -fo="./OBJECTS\Timer.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

OBJECTS/Delay.o : TOOLS/Delay.c TOOLS/Delay.h TOOLS/Delay.c DEFINE/GenericTypeDefs.h ../../MCC18/h/stddef.h
	$(CC) -p=18F4550 /i"C:\Embedded\MCC18\h" "TOOLS\Delay.c" -fo="./OBJECTS\Delay.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

OBJECTS/GlobalTypeVars.o : DEFINE/GlobalTypeVars.c DEFINE/GlobalTypeVars.h DEFINE/GenericTypeDefs.h ../../MCC18/h/stddef.h DEFINE/UserDefs.h
	$(CC) -p=18F4550 /i"C:\Embedded\MCC18\h" "DEFINE\GlobalTypeVars.c" -fo="./OBJECTS\GlobalTypeVars.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

OBJECTS/Temp_Ctrl.o : PCR/Temp_Ctrl.c PCR/Temp_Ctrl.h PCR/Temp_Sensor.h ../../MCC18/h/stdio.h ../../MCC18/h/stdlib.h ../../MCC18/h/string.h PCR/Temp_Ctrl.c DEFINE/GenericTypeDefs.h ../../MCC18/h/stddef.h DEFINE/GlobalTypeVars.h DEFINE/UserDefs.h CONFIG/Compiler.h ../../MCC18/h/p18cxxx.h ../../MCC18/h/p18f4550.h ../../MCC18/h/stdarg.h HardwareProfile.h HardwareProfile\ -\ PICDEM\ FSUSB.h
	$(CC) -p=18F4550 /i"C:\Embedded\MCC18\h" "PCR\Temp_Ctrl.c" -fo="./OBJECTS\Temp_Ctrl.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

OBJECTS/Temp_Sensor.o : PCR/Temp_Sensor.c ../../MCC18/h/stdio.h ../../MCC18/h/stdlib.h ../../MCC18/h/string.h USB/usb_common.h USB/usb_device.h PCR/Temp_Sensor.h PCR/Temp_Sensor.c HardwareProfile.h HardwareProfile\ -\ PICDEM\ FSUSB.h DEFINE/UserDefs.h DEFINE/GenericTypeDefs.h ../../MCC18/h/stddef.h USB/usb.h CONFIG/Compiler.h ../../MCC18/h/p18cxxx.h ../../MCC18/h/p18f4550.h ../../MCC18/h/stdarg.h USB/usb_config.h ../../MCC18/h/limits.h USB/usb_ch9.h USB/usb_hal.h USB/usb_hal_pic18.h USB/usb_function_hid.h DEFINE/GlobalTypeVars.h PCR/Temp_Table.h
	$(CC) -p=18F4550 /i"C:\Embedded\MCC18\h" "PCR\Temp_Sensor.c" -fo="./OBJECTS\Temp_Sensor.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

OBJECTS/Temp_Table.o : PCR/Temp_Table.c ../../MCC18/h/stdio.h ../../MCC18/h/stdlib.h ../../MCC18/h/string.h USB/usb_common.h USB/usb_device.h PCR/Temp_Table.c PCR/Temp_Table.h USB/usb.h CONFIG/Compiler.h ../../MCC18/h/p18cxxx.h ../../MCC18/h/p18f4550.h ../../MCC18/h/stdarg.h ../../MCC18/h/stddef.h DEFINE/GenericTypeDefs.h USB/usb_config.h ../../MCC18/h/limits.h USB/usb_ch9.h USB/usb_hal.h USB/usb_hal_pic18.h
	$(CC) -p=18F4550 /i"C:\Embedded\MCC18\h" "PCR\Temp_Table.c" -fo="./OBJECTS\Temp_Table.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

OBJECTS/State.o : PCR/State.c ../../MCC18/h/stdio.h ../../MCC18/h/stdlib.h ../../MCC18/h/string.h PCR/Temp_Ctrl.h PCR/PCR_Task.h PCR/State.c PCR/State.h DEFINE/GlobalTypeVars.h DEFINE/GenericTypeDefs.h ../../MCC18/h/stddef.h DEFINE/UserDefs.h CONFIG/Compiler.h ../../MCC18/h/p18cxxx.h ../../MCC18/h/p18f4550.h ../../MCC18/h/stdarg.h HardwareProfile.h HardwareProfile\ -\ PICDEM\ FSUSB.h
	$(CC) -p=18F4550 /i"C:\Embedded\MCC18\h" "PCR\State.c" -fo="./OBJECTS\State.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

OBJECTS/Pragma.o : CONFIG/Pragma.c HardwareProfile.h HardwareProfile\ -\ PICDEM\ FSUSB.h
	$(CC) -p=18F4550 /i"C:\Embedded\MCC18\h" "CONFIG\Pragma.c" -fo="./OBJECTS\Pragma.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

OBJECTS/Usb_Task.o : PCR/Usb_Task.c ../../MCC18/h/stdio.h ../../MCC18/h/stdlib.h ../../MCC18/h/string.h USB/usb_common.h USB/usb_device.h TOOLS/Delay.h PCR/Usb_Task.c DEFINE/UserDefs.h DEFINE/GenericTypeDefs.h ../../MCC18/h/stddef.h USB/usb.h CONFIG/Compiler.h ../../MCC18/h/p18cxxx.h ../../MCC18/h/p18f4550.h ../../MCC18/h/stdarg.h USB/usb_config.h ../../MCC18/h/limits.h USB/usb_ch9.h USB/usb_hal.h USB/usb_hal_pic18.h USB/usb_function_hid.h HardwareProfile.h HardwareProfile\ -\ PICDEM\ FSUSB.h DEFINE/GlobalTypeVars.h
	$(CC) -p=18F4550 /i"C:\Embedded\MCC18\h" "PCR\Usb_Task.c" -fo="./OBJECTS\Usb_Task.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "OBJECTS\main.o" "OBJECTS\usb_device.o" "OBJECTS\usb_function_hid.o" "OBJECTS\usb_descriptors.o" "OBJECTS\Init.o" "OBJECTS\PCR_Task.o" "OBJECTS\Timer.o" "OBJECTS\Delay.o" "OBJECTS\GlobalTypeVars.o" "OBJECTS\Temp_Ctrl.o" "OBJECTS\Temp_Sensor.o" "OBJECTS\Temp_Table.o" "OBJECTS\State.o" "OBJECTS\Pragma.o" "OBJECTS\Usb_Task.o" ".\OUTPUT\PeltierPCR.cof" ".\OUTPUT\PeltierPCR.hex"

