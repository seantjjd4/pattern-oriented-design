#include <iostream>

#include "../src/json_object.h"
#include "../src/string_value.h"
#include "../src/json_parser.h"
#include "../src/json_builder.h"
#include "../src/beautify_visitor.h"
#include "../src/visitor.h"

TEST(JSonSuite, OneKeyStringValue) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    ASSERT_EQ(v1, jo->getValue("key1"));
    ASSERT_EQ("{\n\"key1\":\"value1\"\n}", jo->toString());

    delete jo;
    delete v1;

}

TEST(JSonSuite, TwoKeyStringValue) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);
    ASSERT_EQ("\"value1\"", jo->getValue("key1")->toString());
    ASSERT_EQ("\"value2\"", jo->getValue("key2")->toString());
    ASSERT_EQ("{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}", jo->toString());

    delete jo;
    delete v1;
    delete v2;
}

TEST(JSonSuite, Composite) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonObject *j_composite = new JsonObject;
    j_composite->set("keyc", jo);
    ASSERT_EQ(jo, j_composite->getValue("keyc"));
    ASSERT_EQ("{\n\"keyc\":{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}\n}", j_composite->toString());

    delete jo;
    delete v1;
    delete v2;
    delete j_composite;
}

TEST(JSonSuite, CompositeGetValueException) {
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonObject *j_composite = new JsonObject;
    j_composite->set("keyc", jo);
    
    ASSERT_ANY_THROW(j_composite->getValue("keyd"));
    ASSERT_EQ("{\n\"keyc\":{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}\n}", j_composite->toString());

    delete jo;
    delete v1;
    delete v2;
    delete j_composite;
}

TEST(JSonSuite, PaserTest) {
    JsonParser * p = new JsonParser(new JsonScanner(), new JsonBuilder());
    p->setInput("{\n\"keyc\":{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}\n}");
    p->parse();
    JsonObject * j = p->getJsonObject();
    ASSERT_EQ("{\n\"keyc\":{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}\n}", j->toString());

    delete p;
    delete j;
}

TEST(JSonSuite, BuilderTest) {
    JsonBuilder * b = new JsonBuilder();
    b->buildObject("keyc");
    b->buildValue("key1", "value1");
    b->buildValue("key2", "value2");
    b->endObject();
    b->endObject();
    JsonObject * j = b->getJsonObject();
    ASSERT_EQ("{\n\"keyc\":{\n\"key1\":\"value1\",\n\"key2\":\"value2\"\n}\n}", j->toString());

    delete b;
    delete j;
}

TEST(JSonSuite, BeautifyVisitorTest) {
    BeautifyVisitor * v = new BeautifyVisitor();
    JsonObject *jo = new JsonObject;
    Value * v1 = new StringValue("value1");
    jo->set("key1", v1);
    Value * v2 = new StringValue("value2");
    jo->set("key2", v2);

    JsonObject *j_composite = new JsonObject;
    j_composite->set("keyc", jo);

    j_composite->accept(v);

    std::string ans = 
        "{\n"
        "    \"keyc\": {\n"
        "        \"key1\": \"value1\",\n"
        "        \"key2\": \"value2\"\n"
        "    }\n"
        "}";


    ASSERT_EQ(ans, v->getResult());

    delete jo;
    delete v1;
    delete v2;
    delete j_composite;
}