#pragma once

#include "common.hpp"

#include <pugixml.hpp>

namespace Example05
{

int main()
{
    pugi::xml_document doc;

    // get a test document
    // if (doc.load_string("<project><name>test</name><version>1.1</version><public>yes</public></project>"))
    // if (doc.load_string("Hier steht Text aber kein XML."))
    // constexpr auto input{"Hier steht Text <break time=\"200ms\"/> und noch mehr"};
    constexpr auto input{"<say-as>Hier steht Text <break time=\"200ms\"/> und noch mehr</say-as>"};
    if (doc.load_string(input, pugi::parse_full))
    {
      print("succuessful xml loading\n");

      pugi::xml_document result;
      auto speak = result.append_child("speak");
      speak.append_copy(doc.document_element());
      // speak.append_child(pugi::node_null).set_value(input);

      result.print(std::cout);
      std::cout << std::endl;

      pugi::xml_document doc2;

      pugi::xml_node node = doc2.append_child("node");

      // add description node with text child
      pugi::xml_node descr = node.append_child("description");
      descr.append_child(pugi::node_pcdata).set_value("Simple node");

      doc2.save(std::cout);
      std::cout << std::endl;
    }

  return 0;
}

}

