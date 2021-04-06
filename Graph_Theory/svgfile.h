#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED

#include <string>
#include <fstream>
#include <set>
#include <vector>

constexpr char defcol[] = "black";

class Gradient;
class OptionGrad;
class Svgfile
{
    public:
        Svgfile(std::string _filename = "output.svg", int _width=1000, int _height=800);
        ~Svgfile();

        void addDisk(double x, double y, double rx, std::string color=defcol);
        void addCircle(double x, double y, double r, double ep, std::string color=defcol);
        void addDiskGradient(double x, double y, double r, Gradient G);
        void addEllipse(double x, double y, double rx, double ry,  std::string color=defcol);
        void addEllipse2(double x, double y, double rx, double ry, double ep, std::string color, std::string color2);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill=defcol);
        void addRectangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, double x4, double y4, std::string colorFill=defcol);
        void addRectangleGradient(double x1, double y1, double x2, double y2,
                         double x3, double y3, double x4, double y4, Gradient G);
        void addLine(double x1, double y1, double x2, double y2, std::string color=defcol);
        void addCross(double x, double y, double span, std::string color=defcol);

        void addText(double x, double y, std::string text, std::string color=defcol);
        void addText(double x, double y, double val, std::string color=defcol);

        void addGrid(double span=100.0, bool numbering=true, std::string color="lightgrey");

        static std::string makeRGB(int r, int g, int b);

        /// Type non copiable
        Svgfile(const Svgfile&) = delete;
        Svgfile& operator=(const Svgfile&) = delete;

        static bool s_verbose;

    private:
        std::string m_filename;
        std::ofstream m_ostrm;
        int m_width;
        int m_height;

        // Pour éviter les ouverture multiples
        static std::set<std::string> s_openfiles;
};

class OptionGrad
{
    public:
        std::string m_couleur;
        OptionGrad(int offset,int opacity,std::string couleur);
        int m_offset;
        int m_opacity;

};

class Gradient
{
    public:
        Gradient(int x1,int y1,int x2,int y2, std::vector <OptionGrad*>& ListeGrad);
        Gradient();
        std::vector <OptionGrad*> m_ListeGrad;
        int nt;
        int m_x1;
        int m_y1;
        int m_x2;
        int m_y2;

};



#endif // SVGFILE_H_INCLUDED



