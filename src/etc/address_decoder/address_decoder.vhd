library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity address is
 Port (

	 a11 : In std_logic;

	 a10 : In std_logic;


	 ram_cs : Out std_logic;

	 adc_cs : Out std_logic;

	 oled_cs : Out std_logic

 );


 attribute LOC : string;

 attribute LOC of ram_cs : signal is "P19";

 attribute LOC of adc_cs : signal is "P18";

 attribute LOC of oled_cs : signal is "P17";

 attribute LOC of a11 : signal is "P1";

 attribute LOC of a10 : signal is "P2";

end;

architecture behavioral of address is
begin
 -- implement the functionality here

 oled_cs <= NOT ((NOT a10) and (NOT a11));

 adc_cs <= NOT (a10 and (NOT a11));

 ram_cs <= NOT a11;

end behavioral;
