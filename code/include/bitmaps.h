#ifndef BITMAPS_H
#define BITMAPS_H

// 'about-icon', 16x16px
const unsigned char epd_bitmap_about_icon []  = {
	0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x08, 0x10, 0x10, 0x08, 0x10, 0x08, 0x10, 0x08, 0x10, 0x08, 
	0x00, 0x10, 0x01, 0xe0, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00
};
// 'arrow-left', 16x16px
const unsigned char epd_bitmap_arrow_left []  = {
	0x00, 0xc0, 0x01, 0xc0, 0x03, 0xc0, 0x07, 0xc0, 0x1f, 0xc0, 0x3f, 0xc0, 0x7f, 0xc0, 0xff, 0xc0, 
	0x7f, 0xc0, 0x3f, 0xc0, 0x1f, 0xc0, 0x0f, 0xc0, 0x07, 0xc0, 0x03, 0xc0, 0x01, 0xc0, 0x00, 0xc0
};
// 'arrow-right', 16x16px
const unsigned char epd_bitmap_arrow_right []  = {
	0x01, 0x80, 0x01, 0xc0, 0x01, 0xe0, 0x01, 0xf0, 0x01, 0xf8, 0x01, 0xfc, 0x01, 0xfe, 0x01, 0xff, 
	0x01, 0xfe, 0x01, 0xfc, 0x01, 0xf8, 0x01, 0xf8, 0x01, 0xf0, 0x01, 0xe0, 0x01, 0xc0, 0x01, 0x80
};
// 'battery-icon', 16x8px
const unsigned char epd_bitmap_battery_icon []  = {
	0x00, 0x00, 0x7f, 0xf0, 0x7e, 0x08, 0x7f, 0x0c, 0x7f, 0x8c, 0x7f, 0xc8, 0x7f, 0xf0, 0x00, 0x00
};
// 'equalizer-icon', 16x16px
const unsigned char epd_bitmap_equalizer_icon []  = {
	0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x00, 0x00, 0x20, 0x10, 0x20, 0x90, 0x20, 0x10, 0x24, 0x90, 
	0x20, 0x90, 0x24, 0x92, 0x24, 0x90, 0x24, 0x92, 0x24, 0x92, 0x24, 0x92, 0x00, 0x00, 0x00, 0x00
};
// 'icon_home', 16x16px
const unsigned char epd_bitmap_icon_home []  = {
	0x01, 0x00, 0x03, 0x80, 0x07, 0xc0, 0x0f, 0xe0, 0x1f, 0xf0, 0x3f, 0xf8, 0x7f, 0xfc, 0x0f, 0xe0, 
	0x0f, 0xe0, 0x0f, 0xe0, 0x0f, 0xe0, 0x0f, 0xe0, 0x0f, 0xe0, 0x0f, 0xe0, 0x0f, 0xe0, 0x00, 0x00
};
// 'icon_music', 16x16px
const unsigned char epd_bitmap_icon_music []  = {
	0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x3f, 0xfc, 0x30, 0x0c, 0x30, 0x0c, 0x30, 0x0c, 0x30, 0x0c, 
	0x30, 0x0c, 0x30, 0x0c, 0x30, 0x0c, 0x30, 0x0c, 0xc0, 0x30, 0xc0, 0x30, 0x00, 0x00, 0x00, 0x00
};
// 'icon_settings', 16x16px
const unsigned char epd_bitmap_icon_settings []  = {
	0x00, 0x00, 0x00, 0x1c, 0x00, 0x7c, 0x00, 0x60, 0x00, 0x60, 0x00, 0x63, 0x00, 0xe7, 0x01, 0xfe, 
	0x03, 0xfc, 0x07, 0x80, 0x1f, 0x00, 0x1e, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'selected-item-background', 128x20px
const unsigned char epd_bitmap_selected_item_background []  = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
	0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};
// 'shuffle-icon', 16x16px
const unsigned char epd_bitmap_shuffle_icon []  = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x04, 0x3e, 0x3e, 0x01, 0x44, 0x00, 0x88, 0x01, 0x40, 
	0x3e, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'sd-card-info-icon', 16x16px
const unsigned char epd_bitmap_sd_card_info_icon [] PROGMEM = {
	0x00, 0x00, 0x07, 0xfe, 0x1b, 0x6e, 0x3b, 0x6e, 0x5b, 0x6e, 0x5b, 0x6e, 0x40, 0x02, 0x40, 0x02, 
	0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00
};

// 'home', 128x64px
const unsigned char home_screen [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x3f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x3f, 0xf8, 0x08, 0x33, 0xc1, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x80, 0x00, 0x00, 
	0x3f, 0xf8, 0x08, 0x30, 0x21, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x80, 0x00, 0x00, 
	0x3f, 0xf8, 0x08, 0x14, 0x21, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x9e, 0x7c, 0xf8, 
	0x3f, 0xfc, 0x0c, 0x14, 0xa1, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0xa0, 0x44, 0x88, 
	0x3f, 0xfe, 0x0c, 0x14, 0x20, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0xa1, 0x44, 0xf8, 
	0x3f, 0xff, 0x0c, 0x10, 0x20, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0xa0, 0x44, 0x88, 
	0x3f, 0xff, 0x08, 0x13, 0xc0, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x9e, 0x44, 0xf0, 
	0x3f, 0xff, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x3f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x11, 0x8f, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x30, 0x18, 
	0x22, 0x48, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x10, 0xa0, 
	0x26, 0x4e, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x09, 0x15, 0x1c, 
	0x26, 0x41, 0x90, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x09, 0x0b, 0xc4, 
	0x3b, 0xcf, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x07, 0x70, 0x3c, 
	0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x18, 0x00, 0x04, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x40, 0x00, 0x78, 0x00, 0x08, 0x00, 0x06, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0xc0, 0x01, 0xfe, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0xc0, 0x03, 0x03, 0x00, 0x0c, 0x00, 0x07, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x80, 0x06, 0x01, 0x80, 0x04, 0x00, 0x07, 0xe0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x80, 0x04, 0x00, 0x80, 0x04, 0x00, 0x07, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x0f, 0x80, 0x01, 0x80, 0x0c, 0x00, 0xc0, 0x06, 0x00, 0x07, 0xfc, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x1f, 0x80, 0x01, 0x80, 0x0c, 0x00, 0xc0, 0x06, 0x00, 0x07, 0xfe, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x3f, 0x80, 0x01, 0x80, 0x0c, 0x00, 0xc0, 0x06, 0x00, 0x07, 0xfc, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x7f, 0x80, 0x01, 0x80, 0x0c, 0x00, 0xc0, 0x06, 0x00, 0x07, 0xf8, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x7f, 0x80, 0x01, 0x80, 0x04, 0x00, 0x80, 0x06, 0x00, 0x07, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x80, 0x06, 0x01, 0x80, 0x04, 0x00, 0x07, 0xe0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x80, 0x03, 0x02, 0x00, 0x04, 0x00, 0x07, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0xc0, 0x01, 0xfe, 0x00, 0x0c, 0x00, 0x07, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0xc0, 0x00, 0x78, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x40, 0x00, 0x00, 0x00, 0x08, 0x00, 0x06, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x60, 0x00, 0x00, 0x00, 0x18, 0x00, 0x06, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x04, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0xf0, 0x00, 0xb0, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x10, 0x00, 0x80, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x04, 0x40, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x13, 0xcf, 0x97, 0xcf, 0x9e, 0xf5, 0x17, 0x87, 0xf9, 0xf0, 0x40, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0xf4, 0x68, 0x94, 0x68, 0xb2, 0x45, 0x3c, 0x44, 0xc9, 0x11, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0xe7, 0xe8, 0x94, 0x6f, 0xb0, 0x45, 0xaf, 0xc4, 0x49, 0x10, 0x60, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x34, 0x68, 0x94, 0x68, 0xb0, 0x44, 0xec, 0x44, 0x49, 0x14, 0x60, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x17, 0xef, 0x97, 0xcf, 0x9e, 0x64, 0xc7, 0xd4, 0x49, 0xf7, 0xc0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x82, 0x01, 0x86, 0x0c, 0x00, 0x03, 0x80, 0x01, 0xc1, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
};


// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 752)
const int icons_array_length = 11;
const unsigned char* icons_array[icons_array_length] = {
    epd_bitmap_icon_home,
    epd_bitmap_icon_music,
    epd_bitmap_shuffle_icon,
    epd_bitmap_equalizer_icon,
    epd_bitmap_icon_settings,
	epd_bitmap_sd_card_info_icon,
	epd_bitmap_about_icon,
	epd_bitmap_arrow_left,
	epd_bitmap_arrow_right,
	epd_bitmap_battery_icon,
	epd_bitmap_selected_item_background,
	
};

#endif