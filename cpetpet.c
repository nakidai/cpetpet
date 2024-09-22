#include <stdarg.h>
#include <stdio.h>

#include <MagickWand/MagickWand.h>
#include <MagickWand/magick-image.h>
#include <MagickCore/resample.h>
#include <MagickCore/composite.h>
#include <MagickWand/pixel-wand.h>
#include <MagickCore/layer.h>

#include "config.h"


void CPetPet(const char *in, const char *out, const size_t delay)
{
    MagickWand *result, *concat, *hand, *avatar, *edited;
    PixelWand *empty;
    char filenamebuf[128];
    double squeeze;
    double width, height;
    double offset_x, offset_y;

    MagickWandGenesis();

    empty = NewPixelWand();

    result = NewMagickWand();
    concat = NewMagickWand();
    avatar = NewMagickWand();
    concat = NewMagickWand();
    hand   = NewMagickWand();

    PixelSetColor(empty, "none");

    MagickSetImageDispose(result, BackgroundDispose);

    MagickReadImage(avatar, in);
    MagickResizeImage(avatar, 128, 128, Lanczos2Filter);

    for (int i = 0; i < FRAMES; ++i)
    {
        squeeze = (i < FRAMES/2) ? i : FRAMES - i;
        width = 0.8 + squeeze * 0.02;
        height = 0.8 - squeeze * 0.05;
        offset_x = (1 - width) * 0.5 + 0.1;
        offset_y = (1 - height) - 0.08;
        snprintf(filenamebuf, sizeof(filenamebuf), SHAREDIR "/pet%d.gif", i);

        edited = CloneMagickWand(avatar);
        MagickNewImage(concat, MagickGetImageWidth(avatar), MagickGetImageHeight(avatar), empty);
        MagickSetImageDispose(concat, BackgroundDispose);
        MagickSetImageDelay(concat, delay);
        MagickResizeImage(edited, (double)MagickGetImageWidth(avatar)*width, (double)MagickGetImageHeight(avatar)*height, Lanczos2Filter);
        MagickReadImage(hand, filenamebuf);

        MagickCompositeImage(concat, edited, OverCompositeOp, MagickTrue, MagickGetImageWidth(concat)*offset_x, MagickGetImageHeight(concat)*offset_y);
        MagickCompositeImage(concat, hand, OverCompositeOp, MagickTrue, 0, 0);
        MagickAddImage(result, concat);

        ClearMagickWand(concat);
        ClearMagickWand(hand);
    }
    MagickWriteImages(result, out, MagickTrue);

    DestroyMagickWand(result);
    DestroyMagickWand(concat);
    DestroyMagickWand(avatar);
    DestroyMagickWand(edited);
    DestroyMagickWand(hand);

    DestroyPixelWand(empty);

    MagickWandTerminus();
}
