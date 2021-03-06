-------------------------------------------------------------------------------
--! @file         counter_tb.vhd
--! @author       Marc Kossmann
--! @author       Michael Riedel
--! @version      v1.0.0
--! @date         05.12.2014
--! @brief        Testbench for counter component
--! @par History:
--! @details      v0.1.0 23.11.2014 Kossmann
--!               - first draft
--! @details      v0.1.2 28.11.2014 Kossmann
--!               - improved documentation
--! @details      v0.1.3 05.12.2014 Riedel
--!               - corrected formatting and indention
--! @details      v1.0.0 05.12.2014 Riedel & Kossmann
--!               - release milestone 3b
-------------------------------------------------------------------------------

--! Use Standard Library
LIBRARY ieee; 
--! Use Logic Elements
USE ieee.std_logic_1164.all; 

--! @brief Testbench entity
ENTITY counter_tb  IS 
  GENERIC
  (
    --! @brief    Prescaler for PWM-signal.
    --! @details  For this purpose 2,5 ms are used as minimal pulse-width.
    --! @details  The prescaler is calculated with the given and desired frequency
    --!     via the following formula:
    --!     \f{equation*}{
    --!       \text{prescaler}         = \frac{f_{\text{clock}} \text{Hz}}{f_{\text{prescaler}} \text{Hz}}
    --!     \f}
    --!     e.g.:
    --!     \f{equation*}{
    --!       \left.\begin{aligned}
    --!         f_{\text{prescaler}}  &= \frac{2}{5}\,\text{ms} \newline
    --!                               &= 400\,\text{Hz} \newline\newline
    --!         \text{prescaler}      &= \frac{50\,\text{Mhz}}{400\,\text{Hz}} \newline
    --!                               &= 125000 \newline
    --!       \end{aligned}
    --!     \right\}
    --!     \qquad \text{pulse-width: 2.5 ms}
    --!     \f}
    --! @details For simulation-purpose the divider was set to 125 for faster wave generation.
    divider  : INTEGER   := 125
  );
END;

--! @brief    Architecture of testbench
--! @details  Just to test if counter works like expected
ARCHITECTURE counter_tb_arch OF counter_tb IS

  SIGNAL reset_n  :  STD_LOGIC    := '0'; 
  SIGNAL clock    :  STD_LOGIC    := '0'; 
  SIGNAL clk_out  :  STD_LOGIC    := '0'; 
  SIGNAL enable   :  STD_LOGIC    := '0'; 

  COMPONENT counter
    GENERIC
    ( 
      divider     : INTEGER
    );  
    PORT ( 
      reset_n     : IN  STD_LOGIC;
      clock       : IN  STD_LOGIC;
      clk_out     : OUT STD_LOGIC;
      enable      : IN  STD_LOGIC
    ); 
  END COMPONENT;

BEGIN
  DUT  : counter
    GENERIC MAP
    ( 
      divider     => divider
    )
    PORT MAP
    (
      reset_n     => reset_n,
      clock       => clock,
      clk_out     => clk_out,
      enable      => enable
    );
      
    clock         <= NOT clock AFTER 10 ns;
    enable        <= '1' AFTER 20 ns;
    reset_n       <= '1' AFTER 20 ns;
    
    finish_sim_time : PROCESS
    BEGIN
      WAIT FOR 50 ms;
      ASSERT false
        REPORT "simulation finished"
        SEVERITY failure;
  END PROCESS finish_sim_time;
END;

