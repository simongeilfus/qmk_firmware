# MCU name
MCU = STM32F303

# Build Options

TAP_DANCE_ENABLE  		= yes		# Enable TapDance functionality
DYNAMIC_MACRO_ENABLE 	= yes
AUTO_SHIFT_ENABLE 		= yes

BOOTMAGIC_ENABLE 		= yes      	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE 		= yes      	# Mouse keys(+4700)
EXTRAKEY_ENABLE 		= yes       # Audio control and System control(+450)
CONSOLE_ENABLE 			= yes       # Console for debug(+400)
COMMAND_ENABLE 			= yes       # Commands for debug and configuration
NKRO_ENABLE 			= yes     	# Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE 		= no       	# Enable keyboard backlight functionality
MIDI_ENABLE 			= no        # MIDI controls
AUDIO_ENABLE 			= yes       # Audio output on port C6
UNICODE_ENABLE 			= true      # Unicode
UNICODEMAP_ENABLE   	= no   		# Enable extended unicode
BLUETOOTH_ENABLE 		= no   	    # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE 		= yes       # Enable WS2812 RGB underlight.
WS2812_DRIVER 			= bitbang
API_SYSEX_ENABLE 		= no

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE 	= no    	# Breathing sleep LED during USB suspend

# SERIAL_LINK_ENABLE = yes
ENCODER_ENABLE 		= yes
DIP_SWITCH_ENABLE 	= yes

LAYOUTS 			= ortho_5x12