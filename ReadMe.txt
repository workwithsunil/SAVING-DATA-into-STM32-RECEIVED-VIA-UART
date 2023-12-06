PROJECT INFO :
It is for storing address or some critical data of a stm32 into its emulated EEPROM whihc is actually flash memory so as to solve the issue of mass programming

There are two programs in this project right now
1. UART INTRO @INFO :>> This project is storing data from an UART INTERRUPT AND ASSEMBLING DATA on STM32F410RBC(NUCLEO BOARD)
2. EP = Program of an emulated EEPROM, made the library working, but i need something more sophistictaed, i dont need RAM in betwwen, directly the data should be keep storing in the Emulated EEPROM
3.BLACK_PILL_EP_TEST = in this project, stm32 Emulated EEPROM TESTED AND IS WORKING
4.Project TEST1_F410RB ADDED ::>> Contains project that includes outting both uart and eeprom together
5.Working on bare minimum with  STM32F401CCU6 ::> Completed, it is working without consuming any RAM and is working directly with read and write command.