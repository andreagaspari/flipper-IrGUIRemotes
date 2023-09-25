#pragma once

#include "../ir_gui_remotes.h"

const LedRemoteButton led_stripe_btns[] = {
     // First Row (Speed up, Speed Down, On, Off)
     {
          .label = "Speed Up",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xFF00,
               .repeat = false
          },
          .icon = &I_speed_up_15x16,
          .icon_hover = &I_speed_up_hover_15x16
     }, {
          .label = "Speed Down",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xFE01,
               .repeat = false
          },
          .icon = &I_speed_down_15x16,
          .icon_hover = &I_speed_down_hover_15x16
     }, {
          .label = "Off",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xFD02,
               .repeat = false
          },
          .icon = &I_off_15x16,
          .icon_hover = &I_off_hover_15x16
     }, {
          .label = "On",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xFC03,
               .repeat = false
          },
          .icon = &I_on_15x16,
          .icon_hover = &I_on_hover_15x16
     },

     // Second Row (R5, G5, B5, W)
     {
          .label = "Red",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xFB04,
               .repeat = false
          },
          .icon = &I_r5_15x16,
          .icon_hover = &I_r5_hover_15x16
     }, {
          .label = "Green",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xFA05,
               .repeat = false
          },
          .icon = &I_g5_15x16,
          .icon_hover = &I_g5_hover_15x16
     }, {
          .label = "Blue",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xF906,
               .repeat = false
          },
          .icon = &I_b5_15x16,
          .icon_hover = &I_b5_hover_15x16
     }, {
          .label = "White",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xF807,
               .repeat = false
          },
          .icon = &I_w_15x16,
          .icon_hover = &I_w_hover_15x16
     },

     // Third Row (R4, G4, B4, Flash)
     {
          .label = "Orange",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xF708,
               .repeat = false
          },
          .icon = &I_r4_15x16,
          .icon_hover = &I_r4_hover_15x16
     }, {
          .label = "Salad",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xF609,
               .repeat = false
          },
          .icon = &I_g4_15x16,
          .icon_hover = &I_g4_hover_15x16
     }, {
          .label = "Curious Blue",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xF50A,
               .repeat = false
          },
          .icon = &I_b4_15x16,
          .icon_hover = &I_b4_hover_15x16
     }, {
          .label = "Flash",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xF40B,
               .repeat = false
          },
          .icon = &I_flash_15x16,
          .icon_hover = &I_flash_hover_15x16
     },

     // Fouth Row (R3, G3, B3, Strobe)
     {
          .label = "Meteor",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xF30C,
               .repeat = false
          },
          .icon = &I_r3_15x16,
          .icon_hover = &I_r3_hover_15x16
     }, {
          .label = "Malibu",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xF20D,
               .repeat = false
          },
          .icon = &I_g3_15x16,
          .icon_hover = &I_g3_hover_15x16
     }, {
          .label = "Camelot",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xF10E,
               .repeat = false
          },
          .icon = &I_b3_15x16,
          .icon_hover = &I_b3_hover_15x16
     }, {
          .label = "Strobe",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xF00F,
               .repeat = false
          },
          .icon = &I_strobe_15x16,
          .icon_hover = &I_strobe_hover_15x16
     },

     // Fifth Row (R2, G2, B2, Fade)
     { 
          .label = "Dandelion",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xEF10,
               .repeat = false
          },
          .icon = &I_r2_15x16,
          .icon_hover = &I_r2_hover_15x16
     }, {
          .label = "Cerulean",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xEE11,
               .repeat = false
          },
          .icon = &I_g2_15x16,
          .icon_hover = &I_g2_hover_15x16
     }, {
          .label = "Hibiscus",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xED12,
               .repeat = false
          },
          .icon = &I_b2_15x16,
          .icon_hover = &I_b2_hover_15x16
     }, {
          .label = "Fade",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xEC13,
               .repeat = false
          },
          .icon = &I_fade_15x16,
          .icon_hover = &I_fade_hover_15x16
     },

     // Sixth Row (R1, G1, B1, Smooth)
     {
          .label = "Yellow",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xEB14,
               .repeat = false
          },
          .icon = &I_r1_15x16,
          .icon_hover = &I_r1_hover_15x16
     }, {
          .label = "Deep Cerulean",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xEA15,
               .repeat = false
          }, 
          .icon = &I_g1_15x16,
          .icon_hover = &I_g1_hover_15x16
     }, {
          .label = "Mulberry",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xE916,
               .repeat = false
          },
          .icon = &I_b1_15x16,
          .icon_hover = &I_b1_hover_15x16
     }, {
          .label = "Smooth",
          .ir_message = {
               .protocol = InfraredProtocolNECext,
               .address = 0xEF00,
               .command = 0xE817,
               .repeat = false
          },
          .icon = &I_smooth_15x16,
          .icon_hover = &I_smooth_hover_15x16
     }
};

const LedRemote led_stripe_remote = {
     .label = "Led Stripe", 
     .rows = 6, 
     .cols = 4, 
     .buttons = led_stripe_btns
};