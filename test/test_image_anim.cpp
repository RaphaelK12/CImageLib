#include <std_c++.h>
#include <CFile/CFile.h>
#include <CStrUtil/CStrUtil.h>
#include <CFileUtil/CFileUtil.h>
#include <CImageLib/CImageLib.h>

int
main(int argc, char **argv)
{
  char number_string[32];

  //------

  if (argc != 2) exit(1);

  CFile *ifile = new CFile(argv[1]);

  string base   = ifile->getBase();
  string suffix = ifile->getSuffix();

  //------

  CImageAnim *image_anim = CImage::createGIFAnim(ifile);

  //------

  int i = 1;

  CImageAnim::const_iterator pimage_frame1 = image_anim->begin();
  CImageAnim::const_iterator pimage_frame2 = image_anim->end();

  for ( ; pimage_frame1 != pimage_frame2; ++pimage_frame1) {
    CImagePtr image = (*pimage_frame1)->getImage();

    sprintf(number_string, "%02d", i);

    string ofilename = base + "_" + number_string + "." + suffix;

    CFile *ofile = new CFile(ofilename);

    CFileType type = CFileUtil::getImageTypeFromName(ofilename);

    image->write(ofile, type);

    delete ofile;

    i++;
  }

  //------

  delete ifile;

  exit(0);
}
