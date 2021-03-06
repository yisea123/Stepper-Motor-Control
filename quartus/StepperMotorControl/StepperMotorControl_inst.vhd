	component StepperMotorControl is
		port (
			reset_reset_n                    : in    std_logic                     := 'X';             -- reset_n
			clk_clk                          : in    std_logic                     := 'X';             -- clk
			sram_SRAM_OE_N                   : out   std_logic_vector(0 downto 0);                     -- SRAM_OE_N
			sram_SRAM_CE_N                   : out   std_logic_vector(0 downto 0);                     -- SRAM_CE_N
			sram_SRAM_BE_N                   : out   std_logic_vector(1 downto 0);                     -- SRAM_BE_N
			sram_SRAM_D                      : inout std_logic_vector(15 downto 0) := (others => 'X'); -- SRAM_D
			sram_SRAM_A                      : out   std_logic_vector(18 downto 0);                    -- SRAM_A
			sram_SRAM_WE_N                   : out   std_logic_vector(0 downto 0);                     -- SRAM_WE_N
			sw_export                        : in    std_logic_vector(9 downto 0)  := (others => 'X'); -- export
			lcd_RS                           : out   std_logic;                                        -- RS
			lcd_RW                           : out   std_logic;                                        -- RW
			lcd_data                         : inout std_logic_vector(7 downto 0)  := (others => 'X'); -- data
			lcd_E                            : out   std_logic;                                        -- E
			key_export                       : in    std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			hex0_export                      : out   std_logic_vector(6 downto 0);                     -- export
			hex1_export                      : out   std_logic_vector(6 downto 0);                     -- export
			hex2_export                      : out   std_logic_vector(6 downto 0);                     -- export
			hex3_export                      : out   std_logic_vector(6 downto 0);                     -- export
			led9_export                      : out   std_logic;                                        -- export
			registers_conduit_nios_redleds   : out   std_logic_vector(7 downto 0);                     -- redleds
			registers_conduit_nios_greenleds : out   std_logic_vector(7 downto 0);                     -- greenleds
			mcu_conduit_motor_motor_pwm      : out   std_logic_vector(3 downto 0);                     -- motor_pwm
			mcu_conduit_motor_motor_en       : out   std_logic_vector(1 downto 0)                      -- motor_en
		);
	end component StepperMotorControl;

	u0 : component StepperMotorControl
		port map (
			reset_reset_n                    => CONNECTED_TO_reset_reset_n,                    --                  reset.reset_n
			clk_clk                          => CONNECTED_TO_clk_clk,                          --                    clk.clk
			sram_SRAM_OE_N                   => CONNECTED_TO_sram_SRAM_OE_N,                   --                   sram.SRAM_OE_N
			sram_SRAM_CE_N                   => CONNECTED_TO_sram_SRAM_CE_N,                   --                       .SRAM_CE_N
			sram_SRAM_BE_N                   => CONNECTED_TO_sram_SRAM_BE_N,                   --                       .SRAM_BE_N
			sram_SRAM_D                      => CONNECTED_TO_sram_SRAM_D,                      --                       .SRAM_D
			sram_SRAM_A                      => CONNECTED_TO_sram_SRAM_A,                      --                       .SRAM_A
			sram_SRAM_WE_N                   => CONNECTED_TO_sram_SRAM_WE_N,                   --                       .SRAM_WE_N
			sw_export                        => CONNECTED_TO_sw_export,                        --                     sw.export
			lcd_RS                           => CONNECTED_TO_lcd_RS,                           --                    lcd.RS
			lcd_RW                           => CONNECTED_TO_lcd_RW,                           --                       .RW
			lcd_data                         => CONNECTED_TO_lcd_data,                         --                       .data
			lcd_E                            => CONNECTED_TO_lcd_E,                            --                       .E
			key_export                       => CONNECTED_TO_key_export,                       --                    key.export
			hex0_export                      => CONNECTED_TO_hex0_export,                      --                   hex0.export
			hex1_export                      => CONNECTED_TO_hex1_export,                      --                   hex1.export
			hex2_export                      => CONNECTED_TO_hex2_export,                      --                   hex2.export
			hex3_export                      => CONNECTED_TO_hex3_export,                      --                   hex3.export
			led9_export                      => CONNECTED_TO_led9_export,                      --                   led9.export
			registers_conduit_nios_redleds   => CONNECTED_TO_registers_conduit_nios_redleds,   -- registers_conduit_nios.redleds
			registers_conduit_nios_greenleds => CONNECTED_TO_registers_conduit_nios_greenleds, --                       .greenleds
			mcu_conduit_motor_motor_pwm      => CONNECTED_TO_mcu_conduit_motor_motor_pwm,      --      mcu_conduit_motor.motor_pwm
			mcu_conduit_motor_motor_en       => CONNECTED_TO_mcu_conduit_motor_motor_en        --                       .motor_en
		);

