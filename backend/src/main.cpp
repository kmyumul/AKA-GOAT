#include "crow.h"
#include "cpr.h"
#include "nlohmann/json.hpp"
#include <string>
#include <vector>
#include <functional>


int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    app.port(18080).multithreaded().run();
}
