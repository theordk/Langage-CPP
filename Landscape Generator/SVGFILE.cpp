#include "svgfile.h"
#include "math.h"


const std::string svgHeader =
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" ";

const std::string svgEnding = "\n\n</svg>\n";

/// Effets "Boule en relief", voir données à la fin de ce fichier
extern const std::string svgBallGradients;

std::set<std::string> Svgfile::s_openfiles;

Svgfile::Svgfile(std::string _filename, int _width, int _height) :
    m_filename{_filename}, m_width{_width}, m_height{_height}
{

    std::cout << "Opening SVG output file : "
              << m_filename << std::endl;

    if ( s_openfiles.count(m_filename) )
        throw std::runtime_error( "File " + m_filename + " already open !" );

    m_ostrm.open(m_filename);
    s_openfiles.insert(m_filename);

    if (!m_ostrm)
    {
        std::cout << "Problem opening " << m_filename << std::endl;
        throw std::runtime_error("Could not open file " + m_filename );
    }

    std::cout << "OK" << std::endl;

    // Writing the header into the SVG file
    m_ostrm << svgHeader;
    m_ostrm << "width=\"" << m_width << "\" height=\"" << m_height << "\">\n\n";
}

Svgfile::~Svgfile()
{
    // Writing the ending into the SVG file
    m_ostrm << svgEnding;

    // Removing this file from the list of open files
    s_openfiles.erase(m_filename);

    // No need to explicitly close the ofstream object (automatic upon destruction)
}

// Helper templated function
template<typename T>
std::string attrib(std::string name, T val)
{
    std::ostringstream oss;
    oss << name << "=\"" << val << "\" ";
    return oss.str();
}

void Svgfile::addDisk(double x, double y, double r, std::string color, double ep)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", color )
            << attrib("stroke", "black")
            << attrib("stroke-width",ep)
            << "/>\n";
}

void Svgfile::addCircle(double x, double y, double r, double ep, std::string color)
{
    m_ostrm << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", "none")
            << attrib("stroke", color )
            << attrib("stroke-width", ep )
            << "/>\n";
}

/// <polygon points="200,10 250,190 160,210" style="fill:lime;stroke:purple;stroke-width:1" />
void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke)
{

    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << ";stroke:" << colorStroke
            << ";stroke-width:" << thickness
            << "\" />\n";
}


void Svgfile::addTriangle(double x1, double y1, double x2, double y2,
                          double x3, double y3, std::string colorFill)
{
    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << colorFill
            << "\" />\n";
}

void Svgfile::addLine(double x1, double y1, double x2, double y2, std::string color)
{
    m_ostrm << "<line "
            << attrib("x1", x1)
            << attrib("y1", y1)
            << attrib("x2", x2)
            << attrib("y2", y2)
            << attrib("stroke", color)
            << "/>\n";
}

void Svgfile::addCross(double x, double y, double span, std::string color)
{
    addLine(x-span, y-span, x+span, y+span, color);
    addLine(x-span, y+span, x+span, y-span, color);
}

void Svgfile::addText(double x, double y, std::string text, std::string color)
{
    /// <text x="180" y="60">Un texte</text>
    m_ostrm << "<text "
            << attrib("x", x)
            << attrib("y", y)
            << attrib("fill", color)
            << ">" << text << "</text>\n";
}

void Svgfile::addText(double x, double y, double val, std::string color)
{
    std::ostringstream oss;
    oss << val;
    addText(x, y, oss.str(), color);
}

void Svgfile::addGrid(double span, bool numbering, std::string color)
{
    double y=0;
    while (y<=m_height)
    {
        addLine(0, y, m_width, y, color);
        if (numbering)
            addText(5, y-5, y, color);
        y+=span;
    }

    double x=0;
    while (x<=m_width)
    {
        addLine(x, 0, x, m_height, color);
        if (numbering)
            addText(x+5, 15, x, color);
        x+=span;
    }
}

std::string Svgfile::makeRGB(int r, int g, int b)
{
    std::ostringstream oss;
    oss << "rgb(" << r << "," << g << "," << b << ")";
    return oss.str();
}

void Svgfile::addEllipse(double x, double y, double rx, double ry, std::string color)
{
    m_ostrm << "<ellipse "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("rx", rx)
            << attrib("ry", ry)
            << attrib("fill", color)
            << attrib("stroke", color )
            << "/>\n";
}
void Svgfile::addRectangle(double x, double y, double largeur, double hauteur, std::string color, double rx, double ry, double ep)
{
    m_ostrm << "<rect "
            << attrib("x", x)
            << attrib("y", y)
            << attrib("rx", rx)
            << attrib("ry", ry)
            << attrib("width", largeur)
            << attrib("height", hauteur)
            << attrib("fill", color)
            << attrib("stroke", makeRGB(0,0,0))
            << attrib("stroke-width", ep)
            << "/>\n";
}


void Svgfile::addRectGrad(double x, double y, double largeur, double hauteur, std::string color,std::string color2)
{

    m_ostrm <<"<defs>\n"
            <<"<linearGradient "
            <<attrib("id","grad2")
            <<attrib("x1","0%")
            <<attrib("y1","0%")
            <<attrib("x2","0%")
            <<attrib("y2","100%")
            << ">\n<"
            <<attrib("stop offset","0%")
            <<"style=\"stop-color:"
            <<color
            <<"\" />\n<"
            <<attrib("stop offset","100%")
            <<"style=\"stop-color:"
            <<color2
            <<"\" />\n"
            <<"</linearGradient>\n"
            <<"</defs>\n"
            << "<rect "
            << attrib("x", x)
            << attrib("y", y)
            << attrib("width", largeur)
            << attrib("height", hauteur)
            << attrib("fill", "url(#grad2)" )
            << "/>\n";
}

void Svgfile::addPolygone(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, std::string color, int ep)
{
    m_ostrm << "<polygon points=\" "
            << x1 << "," << y1 << " "
            << x2 << "," << y2 << " "
            << x4 << "," << y4 << " "
            << x3 << "," << y3
            << "\" style=\"fill:" << color
            << ";stroke:black"
            << "; stroke-width:" << ep
            << "\" />\n";
}

void Svgfile::addPolygoneTrigo(double x, double y, int r, double angle, int ep, std::string color)
{
    int x2,y2;
    double rad;
    rad=angle*3.14159265/180;
    x2= r*sin(rad);
    y2= r*cos(rad);
    this->addPolygone(x-ep/2,y,x+ep/2, y, x-x2-ep/2,y-y2,x-x2+ep/2,y-y2,color);
}

void Svgfile::addRectangleTrigo(double x, double y, int hauteur, int largeur, double angle, std::string color, int ep)
{
    int x2,y2,decalageX,decalageY;
    double rad;
    rad=angle*3.14159265/180;
    x2= hauteur*sin(rad);
    y2= hauteur*cos(rad);
    rad=-rad;
    decalageX=cos(rad)*largeur/2;
    decalageY=sin(rad)*largeur/2;

    this->addPolygone(x-decalageX,y-decalageY,x+decalageX, y+decalageY, x-x2-decalageX,y-y2-decalageY,x-x2+decalageX,y-y2+decalageY,color,ep);
}

void Svgfile::addTriangleTrigo(double x, double y, int r, double angle, int ep, std::string color)
{
    int x2,y2;
    double rad;
    rad=angle*3.14159265/180;
    x2= r*sin(rad);
    y2= r*cos(rad);
    this->addPolygone(x-ep/2,y,x+ep/2, y, x-x2-ep/4,y-y2,x-x2+ep/4,y-y2,color);
}

void Svgfile::addShadow(double x, double y, double rx, double ry, std::string color)
{
    m_ostrm <<"<defs>\n"
            <<"<filter "
            <<attrib("id","f1")
            <<attrib("x","0")
            <<attrib("y","0")
            <<">\n"
            <<"<feGaussianBlur "
            <<attrib("in","SourceGraphic")
            <<attrib("stdDeviation","8")
            <<" />\n"
            <<"</filter>\n"
            <<"</defs>\n"
            << "<ellipse "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("rx", rx)
            << attrib("ry", ry)
            << attrib("fill", color)
            << attrib("filter", "url(#f1)")
            << "/>\n";
}

void Svgfile::addDiskGrad(double x, double y, double r, std::string color, std::string color2)
{
    m_ostrm <<"<defs>\n"
            <<"<linearGradient "
            <<attrib("id","grad1")
            <<attrib("x1","0%")
            <<attrib("y1","0%")
            <<attrib("x2","100%")
            <<attrib("y2","0%")
            << ">\n<"
            <<attrib("stop offset","0%")
            <<"style=\"stop-color:"
            <<color
            <<"\" />\n<"
            <<attrib("stop offset","100%")
            <<"style=\"stop-color:"
            <<color2
            <<"\" />\n"
            <<"</linearGradient>\n"
            <<"</defs>\n"
            << "<circle "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("r",  r)
            << attrib("fill", "url(#grad1)" )
            << "/>\n";
}

void Svgfile::addAnneau(double x, double y, double rx, double ry, double ep, std::string color)
{
    m_ostrm << "<ellipse "
            << attrib("cx", x)
            << attrib("cy", y)
            << attrib("rx", rx)
            << attrib("ry", ry)
            << attrib("stroke", color)
            << attrib("stroke-width", ep)
            << "/>\n";
}
