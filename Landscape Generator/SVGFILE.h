#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <set>

constexpr char defcol[] = "black";

class Svgfile
{
    public:
        Svgfile(std::string _filename = "output.svg", int _width=1000, int _height=900);
        ~Svgfile();

        void addDisk(double x, double y, double r, std::string color=defcol, double ep=0);
        void addCircle(double x, double y, double r, double ep, std::string color=defcol);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill=defcol);
        void addEllipse(double x, double y, double rx, double ry, std::string color=defcol);
        void addAnneau(double x, double y, double rx, double ry, double ep, std::string color=defcol);
        void addRectangle(double x, double y, double largeur, double hauteur, std::string color=defcol, double rx=0, double ry=0, double ep=0);
        void addLine(double x1, double y1, double x2, double y2, std::string color=defcol);
        void addCross(double x, double y, double span, std::string color=defcol);
        void addPolygone(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, std::string color=defcol, int ep=0);
        void addPolygoneTrigo(double x, double y, int r, double angle, int ep, std::string color=defcol);
        void addRectangleTrigo(double x, double y, int hauteur, int largeur, double angle, std::string color=defcol, int ep=0);
        void addTriangleTrigo(double x, double y, int r, double angle, int ep, std::string color=defcol);
        void addShadow(double x, double y, double rx, double ry, std::string color=defcol);
        void addDiskGrad(double x, double y, double r, std::string color=defcol, std::string color2=defcol);
        void addRectGrad(double x, double y, double largeur, double hauteur, std::string color=defcol,std::string color2=defcol);

        void addText(double x, double y, std::string text, std::string color=defcol);
        void addText(double x, double y, double val, std::string color=defcol);

        void addGrid(double span=100.0, bool numbering=true, std::string color="lightgrey");


        static std::string makeRGB(int r, int g, int b);

        /// Type non copiable
        Svgfile(const Svgfile&) = delete;
        Svgfile& operator=(const Svgfile&) = delete;

    private:
        std::string m_filename;
        std::ofstream m_ostrm;
        int m_width;
        int m_height;

        // Pour éviter les ouverture multiples
        static std::set<std::string> s_openfiles;
};

#endif // SVGFILE_H_INCLUDED



