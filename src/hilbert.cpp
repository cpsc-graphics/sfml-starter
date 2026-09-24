#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

class hilbert: sf::Transformable{

private:

    float linelength(int n){
        float floatn = (float)n;
        return (std::pow(2,floatn))-1;
    }

    float scalefactor(int n){
        return linelength(n-1)/linelength(n);
    }

    float lengthofeachline(int n){
        return (1/linelength(n))*1004.f;
    }

    float previous(int n){
        return (float)std::pow(2,(n-1))-1;
    }

    float lengthofeachquadrant(int n){
        return lengthofeachline(n)*previous(n);
    }

public:

    sf::VertexArray hilbertrecursion(int n, sf::RenderWindow& window){
        if(n == 1){
            sf::VertexArray firsthilbert(sf::PrimitiveType::LineStrip, 4);

            firsthilbert[0].position = sf::Vector2f(10.f,1014.f);
            firsthilbert[0].color = sf::Color::Black;

            firsthilbert[1].position = sf::Vector2f(10.f,10.f);
            firsthilbert[1].color = sf::Color::Black;

            firsthilbert[2].position = sf::Vector2f(1014.f,10.f);
            firsthilbert[2].color = sf::Color::Black;

            firsthilbert[3].position = sf::Vector2f(1014.f,1014.f);
            firsthilbert[3].color = sf::Color::Black;

            return firsthilbert;
        }
        
        sf::VertexArray previoushilbert = hilbertrecursion(n-1,window);

        sf::VertexArray returnarray(sf::PrimitiveType::LineStrip);//array to add all vertices to

        sf::VertexArray topleft = previoushilbert;//copy for topleft
        sf::VertexArray topright = previoushilbert;//copy for topright
        sf::VertexArray bottomleft = previoushilbert;//copy for bottomleft
        sf::VertexArray bottomright = previoushilbert;//copy for bottomright

        sf::Transform transformbl;
        transformbl.translate({lengthofeachquadrant(n),lengthofeachline(n)+lengthofeachquadrant(n)});
        transformbl.translate({10.f,10.f});
        transformbl.rotate(sf::degrees(90));
        transformbl.scale({scalefactor(n),scalefactor(n)});
        transformbl.translate({-10.f,-10.f});
        for(int i = bottomleft.getVertexCount()-1;i>=0;i--){
            bottomleft[i].position = transformbl.transformPoint(bottomleft[i].position);
            returnarray.append(bottomleft[i]);
        } 

        sf::Transform transformtl;
        transformtl.translate({10.f,10.f});
        transformtl.scale({scalefactor(n),scalefactor(n)});
        transformtl.translate({-10.f,-10.f});
        for(int i = 0; i<topleft.getVertexCount();i++){
            topleft[i].position = transformtl.transformPoint(topleft[i].position);
            returnarray.append(topleft[i]);
        }

        sf::Transform transformtr;
        transformtr.translate({lengthofeachline(n)+lengthofeachquadrant(n),0.f});
        transformtr.translate({10.f,10.f});
        transformtr.scale({scalefactor(n),scalefactor(n)});
        transformtr.translate({-10.f,-10.f});
        for(int i = 0; i<topright.getVertexCount();i++){
            topright[i].position = transformtr.transformPoint(topright[i].position);
            returnarray.append(topright[i]);
        }

        sf::Transform transformbr;
        transformbr.translate({lengthofeachline(n)+lengthofeachquadrant(n),lengthofeachline(n)+(2*lengthofeachquadrant(n))});
        transformbr.translate({10.f,10.f});
        transformbr.rotate(sf::degrees(-90));
        transformbr.scale({scalefactor(n),scalefactor(n)});
        transformbr.translate({-10.f,-10.f});
        for(int i = bottomright.getVertexCount()-1;i>=0;i--){
            bottomright[i].position = transformbr.transformPoint(bottomright[i].position);
            returnarray.append(bottomright[i]);
        }

        return returnarray;
    }
};