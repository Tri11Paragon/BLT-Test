//
// Created by brett on 7/29/23.
//
#include <iostream>

#include <blt/window.h>
#include <blt/std/logging.h>
#include <blt/renderer/engine.h>
#include <blt/parse/argparse.h>
#include <blt/std/time.h>

using namespace blt::graphics;

void runGraphics(int argc, const char** argv)
{
    Settings settings;
    settings.setProperty(properties_t::WINDOW_WIDTH, Settings::property_t(1440));
    settings.setProperty(properties_t::WINDOW_HEIGHT, Settings::property_t(720));
    settings.setProperty(properties_t::WINDOW_RESIZABLE, Settings::property_t(true));
    settings.setProperty(properties_t::WINDOW_TITLE, Settings::property_t("So You Think You Can Park?"));
    
    // TODO: poll hardware
    resources::init(16);
    // TODO local
    resources::loadTexture("/home/brett/git/parksandrec/resources/textures/test.png", "test.png");
    
    Window::create(settings);
    
    resources::beginLoading();
    
    Engine gameEngine(settings);
    //Window::setMouseVisible(false);
    gameEngine.run();
    
    resources::cleanup();
    
    BLT_INFO("Engine has stopped running. Have a nice day!");
}

void runBLT(int argc, const char** argv)
{
    blt::arg_parse parser;
    parser.setHelpExtras("blt");
    parser.addArgument(blt::arg_builder("--hashmaps").setAction(blt::arg_action_t::STORE_TRUE).setHelp("Test hashmap implementations").build());
    parser.addArgument(blt::arg_builder("--nbt").setAction(blt::arg_action_t::STORE_TRUE).setHelp("Test NBT implementations").build());
    parser.addArgument(blt::arg_builder("--functions").setAction(blt::arg_action_t::STORE_TRUE)
                                                      .setHelp("Test various function implementations").build());
    parser.addArgument(blt::arg_builder("run_size").setAction(blt::arg_action_t::STORE).setNArgs(1)
                                                   .setHelp("Number of iterations to run of each performance test.").build());
    auto args = parser.parse_args(argc, argv);
    
    if (args.contains("--hashmaps"))
    {
        BLT_TRACE("Hello there!");
    }
    
    if (args.contains("--functions"))
    {
        BLT_INFO("Hello there! 2");
    }
    
    BLT_TRACE(args.contains("run_size"));
    BLT_TRACE(blt::arg_parse::get_cast<int>(args["run_size"]));
    
    BLT_TRACE("SUp");
}

int main(int argc, const char** argv)
{
    // has no way of knowing that --functions is fine.
    blt::arg_parse parser;
    parser.addArgument(
            blt::arg_builder("graphics").setAction(blt::arg_action_t::STORE_TRUE).setHelp("Enable graphical interface and testing of blt::graphics")
                                        .disableHelp().build());
    parser.addArgument(
            blt::arg_builder("blt").setAction(blt::arg_action_t::STORE_TRUE).setHelp("Enable testing of generic BLT libraries").disableHelp()
                                   .build());
    parser.addArgument(blt::arg_builder("-c", "--no-color").setAction(blt::arg_action_t::STORE_TRUE).build());
    
    auto args = parser.parse_args(argc, argv);
    
    if (args.contains("--no-color"))
    {
        for (int i = (int) blt::logging::log_level::NONE; i < (int) blt::logging::log_level::FATAL; i++)
            blt::logging::setLogColor((blt::logging::log_level) i, "");
        blt::logging::setLogOutputFormat("[${{TIME}}] [${{LOG_LEVEL}}] (${{FILE}}:${{LINE}}) ${{STR}}\n");
    }
    
    if (args.contains("graphics"))
        runGraphics(argc, argv);
    if (args.contains("blt"))
        runBLT(argc, argv);
    
}