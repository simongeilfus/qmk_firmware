#pragma once

void tap( uint16_t keycode )
{
    register_code(keycode);
    unregister_code(keycode);
};
