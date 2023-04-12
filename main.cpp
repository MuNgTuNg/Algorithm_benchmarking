#include <sApp.hpp>


void parseCLI(int argc, char *argv[], shb::sApp& app){
    for(int i = 0; i < argc; ++i){
        if(strcmp("algorithms",argv[i]) == 0){
            app.algorithms = true;
        }
        if(strcmp("graphics",argv[i]) == 0){
            app.graphics = true;
        }
        if(strcmp("graph",argv[i]) == 0){
            app.graph = true;
        }
        if(strcmp("list",argv[i]) == 0){
            app.list = true;
        }
        if(strcmp("tree",argv[i]) == 0){
            app.tree = true;
        }
    }
}

int main(int argc, char *argv[]){
    
    shb::sApp app;
   
    parseCLI(argc,argv, app);

    app.run();

    return 0;
}