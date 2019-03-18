----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11.03.2019 11:14:43
-- Design Name: 
-- Module Name: ctrl_mouse_plasma - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ctrl_mouse_plasma is
  port(
   		clock			: in  std_logic;
		reset			: in  std_logic;
		
		OUTPUT_X		: out std_logic_vector(31 downto 0);
		OUTPUT_Y		: out std_logic_vector(31 downto 0);
		OUTPUT_Z        : out std_logic_vector(31 downto 0);
		
        BOUTON_L        : out std_logic;
        BOUTON_M        : out std_logic;
        BOUTON_R        : out std_logic;
		
		ps2_clk     : inout std_logic;
		ps2_data    : inout std_logic
		
);
end ctrl_mouse_plasma;

architecture Behavioral of ctrl_mouse_plasma is

SIGNAL mouse_x 	: std_logic_vector(11 downto 0);
SIGNAL mouse_y 	: std_logic_vector(11 downto 0);
SIGNAL mouse_z 	: std_logic_vector(3 downto 0);

  COMPONENT MouseCtl
  GENERIC
  (
     SYSCLK_FREQUENCY_HZ : integer := 100000000;
     CHECK_PERIOD_MS     : integer := 500;
     TIMEOUT_PERIOD_MS   : integer := 100
  );
  PORT(
      clk : IN std_logic;
      rst : IN std_logic;
      value : IN std_logic_vector(11 downto 0);
      setx : IN std_logic;
      sety : IN std_logic;
      setmax_x : IN std_logic;
      setmax_y : IN std_logic;    
      ps2_clk : INOUT std_logic;
      ps2_data : INOUT std_logic;      
      xpos : OUT std_logic_vector(11 downto 0);
      ypos : OUT std_logic_vector(11 downto 0);
      zpos : OUT std_logic_vector(3 downto 0);
      left : OUT std_logic;
      middle : OUT std_logic;
      right : OUT std_logic;
      new_event : OUT std_logic
      );
  END COMPONENT;

begin
	
	OUTPUT_X <= "00000000000000000000"&mouse_x;
	OUTPUT_Y <= "00000000000000000000"&mouse_y;
    OUTPUT_Z <= "0000000000000000000000000000"&mouse_z;
    
    ----------------------------------------------------------------------------------
    -- Mouse Controller
    ----------------------------------------------------------------------------------
       Inst_MouseCtl: MouseCtl
       GENERIC MAP
    (
       SYSCLK_FREQUENCY_HZ => 108000000,
       CHECK_PERIOD_MS     => 500,
       TIMEOUT_PERIOD_MS   => 100
    )
       PORT MAP
       (
          clk            => clock,
          rst            => reset,
          xpos           => MOUSE_X,
          ypos           => MOUSE_Y,
          zpos           => mouse_z,
          left           => BOUTON_L,
          middle         => BOUTON_M,
          right          => BOUTON_R,
          new_event      => open,
          value          => x"000",
          setx           => '0',
          sety           => '0',
          setmax_x       => '0',
          setmax_y       => '0',
          ps2_clk        => PS2_CLK,
          ps2_data       => PS2_DATA
       );
       
       

end Behavioral;
