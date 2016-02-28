#include "pugixml.hpp"
#include <iostream>
#include <cstdio>

int main(int argc, char *argv[]){
    std::string file = argv[0];
    std::string save;
    int i = file.find("\\");
    while(i > 0)
    {
        save = file.substr(0,i);
        file = file.substr(i+1);
        i = file.find("\\");
    }

pugi::xml_parse_result res;
pugi::xml_document doc;
res = doc.load_file(save.c_str(),pugi::parse_full);

pugi::xml_node tools = doc.child("SaveGame").child("locations");
for (pugi::xml_node tool = tools.child("GameLocation"); tool; tool = tool.next_sibling("GameLocation"))
    {

        std::string name = tool.attribute("xsi:type").value();
        if (!name.empty() && std::distance(tool.child("objects").children().begin(), tool.child("objects").children().end())>0)
            {
                std::cout << name << std::endl;
                for (pugi::xml_node objects : tool.child("objects").children())
                {
                    std::string objName = objects.child("value").child("Object").child("Name").text().get();

                    //Filtering objects
                    if (objName.compare("Weeds")!=0 && objName.compare("Stone")!=0 && objName.compare("Twig")!=0)
                    {
                        std::cout << objName << std::endl;
                        std::cout << "x : " << objects.child("key").child("Vector2").child("X").text().get() << std::endl <<  "y : " <<objects.child("key").child("Vector2").child("Y").text().get() << std::endl;
                    }
                }
                std::cout << std::endl;
            }
    }
    getchar();
}
