#include <FaNES.h>

const uchar updateNametableListInit[6 * 3 + 13 + 11 + 1] = {
    MSB(NAMETABLE_A_POSITION(4, 2)), LSB(NAMETABLE_A_POSITION(4, 2)), '0',
    MSB(NAMETABLE_A_POSITION(5, 2)), LSB(NAMETABLE_A_POSITION(5, 2)), '0',
    MSB(NAMETABLE_A_POSITION(6, 2)), LSB(NAMETABLE_A_POSITION(6, 2)), '0',
    MSB(NAMETABLE_A_POSITION(10, 2)), LSB(NAMETABLE_A_POSITION(10, 2)), '0',
    MSB(NAMETABLE_A_POSITION(11, 2)), LSB(NAMETABLE_A_POSITION(11, 2)), '0',
    MSB(NAMETABLE_A_POSITION(12, 2)), LSB(NAMETABLE_A_POSITION(12, 2)), '0',
    MSB(NAMETABLE_A_POSITION(2, 4)) | UPDATE_NAMETABLE_HORIZONTAL, LSB(NAMETABLE_A_POSITION(2, 4)), 10, 'H', 'O', 'R', 'I', 'Z', 'O', 'N', 'T', 'A', 'L',
    MSB(NAMETABLE_A_POSITION(2, 6)) | UPDATE_NAMETABLE_VERTICAL, LSB(NAMETABLE_A_POSITION(2, 6)), 8, 'V', 'E', 'R', 'T', 'I', 'C', 'A', 'L',
    UPDATE_NAMETABLE_END
};

static uchar updateNametableList[6 * 3 + 13 + 11 + 1];

static uchar cursorX = 124, cursorY = 134;
static uchar pad;

void main() {
    setPaletteColor(PALETTE_BACKGROUND_1 + 0, 0x0F);
    setPaletteColor(PALETTE_BACKGROUND_1 + 3, 0x21);
    setPaletteColor(PALETTE_SPRITE_1 + 3, 0x30);
    printNametableString(NAMETABLE_A_POSITION(2, 2), "X:--- Y:");
    copy(updateNametableList, updateNametableListInit, sizeof(updateNametableListInit));
    updateNametable(updateNametableList);
    newSprite(cursorX, cursorY, 0x0E, NULL, 0);
    onGraphics();
    while(TRUE) {
        pad = padPool(PAD_PORT_PLAYER_1);

        if(pad & PAD_BUTTON_LEFT && cursorX > 0) cursorX -= 2;
        if(pad & PAD_BUTTON_RIGHT && cursorX < 254) cursorX += 2;
        if(pad & PAD_BUTTON_UP && cursorY > 0) cursorY -= 2;
        if(pad & PAD_BUTTON_DOWN && cursorY < 240) cursorY += 2;

        setSpritePosition(cursorX, cursorY, 0);

        updateNametableList[2] = 0x30 + cursorX / 100;
        updateNametableList[5] = 0x30 + cursorX / 10 % 10;
        updateNametableList[8] = 0x30 + cursorX % 10;

        updateNametableList[11] = 0x30 + cursorY / 100;
        updateNametableList[14] = 0x30 + cursorY / 10 % 10;
        updateNametableList[17] = 0x30 + cursorY % 10;
        waitFrame();
    }
}
