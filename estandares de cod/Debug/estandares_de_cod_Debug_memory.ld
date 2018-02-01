/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-2013
 * (c) NXP Semiconductors 2013-2018
 * Generated linker script file for Generic-M4
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.23
 * MCUXpresso IDE v10.1.1 [Build 606] [2018-01-02]  on Jan 22, 2018 8:01:31 AM
 */

MEMORY
{
  /* Define each memory region */
  RamLoc (rwx) : ORIGIN = 0x0, LENGTH = 0x4000 /* 16K bytes (alias RAM) */  
}

  /* Define a symbol for the top of each memory region */
  __base_RamLoc = 0x0  ; /* RamLoc */  
  __base_RAM = 0x0 ; /* RAM */  
  __top_RamLoc = 0x0 + 0x4000 ; /* 16K bytes */  
  __top_RAM = 0x0 + 0x4000 ; /* 16K bytes */  
