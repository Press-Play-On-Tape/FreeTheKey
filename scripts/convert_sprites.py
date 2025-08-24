from PIL import Image
import os
from pathlib import Path

def get_shade(rgba, shades, shade):
    if rgba[0] == 252 and rgba[1] == 111 and rgba[2] == 207 and rgba[3] == 255: 
        return 0

    w = (254 + shades) // shades
    b = (shade + 1) * w
    return 1 if rgba[0] >= b else 0

def get_mask(rgba):

    if rgba[0] == 252 and rgba[1] == 111 and rgba[2] == 207 and rgba[3] == 255: 
        return 0
    return 1 if rgba[3] >= 128 else 0

def convert(fname, shades, sw = None, sh = None, num = None, maskImage = False):

    if not (shades >= 2 and shades <= 4):
        print('shades argument must be 2, 3, or 4')
        return None

    im = Image.open(fname).convert('RGBA')
    pixels = list(im.getdata())
    
    masked = maskImage
    q = 0
    for i in pixels:
        q = q + 1
        # print(i[0])
        # print(i[1])
        # print(i[2])
        # print(i[3])
        if i[0] == 252 and i[1] == 111 and i[2] == 207 and i[3] == 255: 
            masked = True
            break
        if i[3] < 255:
            # print('masked!!! ')
            # print(q)
            masked = True
            # exit()
            break

    print('{}, shades {}, masked {}'.format(fname, shades, masked))


    w = im.width
    h = im.height
    if sw is None: sw = w
    if sh is None: sh = h
    nw = w // sw
    nh = h // sh
    if num is None: num = nw * nh
    sp = (sh + 7) // 8
    
    if nw * nh <= 0:
        print('%s: Invalid sprite dimensions' % fname)
        return None
        
    bytes = bytearray([sw, sh])
    
    for n in range(num):
        bx = (n % nw) * sw
        by = (n // nw) * sh
        for shade in range(shades - 1):
            for p in range(sp):
                for ix in range(sw):
                    x = bx + ix
                    byte = 0
                    mask = 0
                    for iy in range(8):
                        y = p * 8 + iy
                        if y >= sh: break
                        y += by
                        i = y * w + x
                        rgba = pixels[i]
                        byte |= (get_shade(rgba, shades, shade) << iy)
                        mask |= (get_mask(rgba) << iy)
                    bytes += bytearray([byte])
                    if masked:
                        bytes += bytearray([mask])
    
    return bytes
    
def convert_header(fname, fout, sym, shades, sw = None, sh = None, num = None, maskImage = False):
    bytes = convert(fname, shades, sw, sh, num, maskImage)
    if bytes is None: return
    with open(fout, 'a') as f:
        # f.write('#pragma once\n\n#include <stdint.h>\n#include <avr/pgmspace.h>\n\n')
        # f.write('constexpr uint8_t %s[] PROGMEM =\n{\n' % sym)
        f.write('uint8_t %s[] = {\n  ' % sym)
        for n in range(len(bytes)):
            if n % 16 == 2:
                f.write('\n  ')
            f.write('%3d,' % bytes[n])
            # f.write(' ' if n % 16 != 15 else '\n')
            # f.write(' ' if n % 18 != 2 else '\n')
            f.write(' ')
        if len(bytes) % 16 != 2:
            f.write('\n')
        f.write('};\n\n')

def deleteFile(filename):
    if os.path.isfile(filename):
        os.remove(filename)

BASE = './images/'
IMAGES = '../images/'

deleteFile(BASE + 'Images.hpp')

convert_header(IMAGES + 'Titles/PPOT.png',                                                      BASE + 'Images.hpp', 'PPOT', 4, 65, 32)
convert_header(IMAGES + 'Titles/FreeTheKey.png',                                                BASE + 'Images.hpp', 'FreeTheKey', 4, 128, 64)
convert_header(IMAGES + 'Titles/Free.png',                                                      BASE + 'Images.hpp', 'Title_Free', 4)
convert_header(IMAGES + 'Titles/The.png',                                                       BASE + 'Images.hpp', 'Title_The', 4)
convert_header(IMAGES + 'Titles/Key.png',                                                       BASE + 'Images.hpp', 'Title_Key', 4)
convert_header(IMAGES + 'Titles/Background_128x64.png',                                         BASE + 'Images.hpp', 'Background_128x64', 4, 128, 64)
convert_header(IMAGES + 'Titles/Switch.png',                                                    BASE + 'Images.hpp', 'Switch', 4)

convert_header(IMAGES + 'Background.png',                                                       BASE + 'Images.hpp', 'Background', 4, 128, 64)
convert_header(IMAGES + 'Menu.png',                                                             BASE + 'Images.hpp', 'Menu', 4, 45, 24)
convert_header(IMAGES + 'Blocks/Block_12.png',                                                  BASE + 'Images.hpp', 'Block_12', 4, 11, 24)
convert_header(IMAGES + 'Blocks/Block_13.png',                                                  BASE + 'Images.hpp', 'Block_13', 4, 11, 32)
convert_header(IMAGES + 'Blocks/Block_21.png',                                                  BASE + 'Images.hpp', 'Block_21', 4, 21, 16)
convert_header(IMAGES + 'Blocks/Block_31.png',                                                  BASE + 'Images.hpp', 'Block_31', 4, 31, 16)
convert_header(IMAGES + 'Blocks/Key.png',                                                       BASE + 'Images.hpp', 'Key', 4, 21, 16)
convert_header(IMAGES + 'Blocks/Cursor.png',                                                    BASE + 'Images.hpp', 'Cursor', 4, 11, 16)
convert_header(IMAGES + 'Levels.png',                                                           BASE + 'Images.hpp', 'Levels', 4, 16, 16)
convert_header(IMAGES + 'Levels_Cursor.png',                                                    BASE + 'Images.hpp', 'Levels_Cursor', 4)
convert_header(IMAGES + 'Levels_HUD.png',                                                       BASE + 'Images.hpp', 'Levels_HUD', 4, 53, 64)
convert_header(IMAGES + 'Levels_Status.png',                                                    BASE + 'Images.hpp', 'Levels_Status', 4, 43, 8)
convert_header(IMAGES + 'Levels_Number.png',                                                    BASE + 'Images.hpp', 'Levels_Number', 4, 11, 8)
convert_header(IMAGES + 'Levels_NumberOfMoves.png',                                             BASE + 'Images.hpp', 'Levels_NumberOfMoves', 4)
convert_header(IMAGES + 'Levels_NumberOfMoves_Numbers.png',                                     BASE + 'Images.hpp', 'Levels_NumberOfMoves_Numbers', 4, 5, 8)

convert_header(IMAGES + 'Numbers/Numbers_5x3_1D_MB.png',                                        BASE + 'Images.hpp', 'Numbers_5x3_1D_MB', 4, 3, 8)
convert_header(IMAGES + 'Numbers/Numbers_5x3_2D_MB.png',                                        BASE + 'Images.hpp', 'Numbers_5x3_2D_MB', 4, 7, 8)

