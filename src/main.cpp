//============================================================================
// Name        : SplashScreen.cpp
// Author      : hw
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdlib>
#include <iostream>
#include <gst/gst.h>
#include <glib-object.h>

int timeForFade = 66;	//frames /30FPS //2Seconds
int gloopFrame = 0;
int fpsIntervalMillis = 1./30*1000;	//30fps
float duration = 2.0;

struct pipenloop{
	GstElement* p;
	GMainLoop* l;
};

static gboolean on_message(GstBus *bus, GstMessage *message, gpointer user_data) {
    switch (GST_MESSAGE_TYPE(message)) {
        case GST_MESSAGE_EOS:
            g_print("End of stream\n");
            g_main_loop_quit((GMainLoop*)user_data);
            break;
        case GST_MESSAGE_ERROR: {
            GError *error;
            gchar *debug_info;
            gst_message_parse_error(message, &error, &debug_info);
            g_printerr("Error: %s\n", error->message);
            g_error_free(error);
            g_free(debug_info);
            g_main_loop_quit((GMainLoop*)user_data);
            break;
        }
        default:
            break;
    }
    return TRUE;
}



static gboolean query_position(pipenloop* _pnl){
	if(gloopFrame >= 66){
//		std::cout << "EOS" << std::endl;
		gst_element_set_state(_pnl->p, GST_STATE_NULL);
		g_main_loop_quit((GMainLoop*)_pnl->l);
		return FALSE;
//		g_main_loop_quit((GMainLoop*)user_data);
	}
	/*
    GValue alpha = G_VALUE_INIT;
    g_value_init(&alpha, G_TYPE_FLOAT);
    g_value_set_float(&alpha, gloopFrame/timeForFade);
    g_object_set_property(G_OBJECT(pipeline), "alpha", &alpha);
    */
//	std::cout << gloopFrame << std::endl;
    gloopFrame += 1;


    return TRUE;
}



int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);
    std::string fileLocation = "";

    if (argc < 3) {
          g_print("Usage: %s <image-file> <duration-seconds>\n", argv[0]);
          return -1;
      }
    else{
    	fileLocation = argv[1];
    	char *endptr;
        duration = strtof(argv[2], &endptr);
        timeForFade = fpsIntervalMillis * duration;
        if (*endptr != '\0')
            printf("%s is not convertible to float\n", argv[1]);
        else
            printf("%f\n", duration); //0.000000
    }

    //gst-launch-1.0 filesrc location=PXL_20240116_150403266.jpg ! jpegdec ! videoconvert ! imagefreeze num-buffers=200 ! waylandsink window-width=2160 window-height=3840

    std::cout << "CreateElements" << std::endl;
    GstElement *pipeline = gst_pipeline_new("pipeline");
    GstElement *filesrc = gst_element_factory_make("filesrc", "filesrc");
    GstElement *jpegdec = gst_element_factory_make("jpegdec", "jpegdec");
    GstElement *imagefreeze = gst_element_factory_make("imagefreeze", "imagefreeze");
    GstElement *alpha = gst_element_factory_make("alpha", "alpha");
    GstElement *glimagesink = gst_element_factory_make("glimagesink", "glimagesink");
    GstElement *waylandsink = gst_element_factory_make("waylandsink", "waylandsink");


    std::cout << "CreateWidth" << std::endl;
    //2160 3840
    // Create a GValue for width
    GValue width = G_VALUE_INIT;
    g_value_init(&width, G_TYPE_INT);
    g_value_set_int(&width, 2160);

    // Create a GValue for height
    GValue height = G_VALUE_INIT;
    g_value_init(&height, G_TYPE_INT);
    g_value_set_int(&height, 3840);

    // Create a GValue for height
    GValue top = G_VALUE_INIT;
    g_value_init(&top, G_TYPE_INT);
    g_value_set_int(&top, 0);

    /*
    GValue new_dimensions = G_VALUE_INIT;
    g_value_init(&new_dimensions, GST_TYPE_ARRAY);
    gst_value_array_append_value(&new_dimensions, &top);
    gst_value_array_append_value(&new_dimensions, &top);
    gst_value_array_append_value(&new_dimensions, &width);
    gst_value_array_append_value(&new_dimensions, &height);


    std::cout << "Set:Width/Height" << std::endl;
    g_object_set_property(G_OBJECT(glimagesink), "render-rectangle", &new_dimensions);


    GValue sync = G_VALUE_INIT;
    g_value_init(&sync, G_TYPE_INT);
    g_value_set_int(&sync, 0);

    std::cout << "Set:Width/Height" << std::endl;
    g_object_set_property(G_OBJECT(glimagesink), "sync", &sync);
	*/

   /*
    GValue numBuffers = G_VALUE_INIT;
    g_value_init(&numBuffers, G_TYPE_INT);
    g_value_set_int(&numBuffers, 100);
    g_object_set_property(G_OBJECT(imagefreeze), "num-buffers", &numBuffers);
*/
    /*
    GValue numBuffers = G_VALUE_INIT;
    g_value_init(&numBuffers, G_TYPE_INT);
    g_value_set_int(&numBuffers, 1);
    g_object_set_property(G_OBJECT(imagefreeze), "is-live", &numBuffers);
    */

    g_object_set_property(G_OBJECT(waylandsink), "window-width", &width);
    g_object_set_property(G_OBJECT(waylandsink), "window-height", &height);


    g_object_set(G_OBJECT(filesrc), "location", fileLocation.c_str(), NULL);
    std::cout << "Set:File = " << fileLocation << std::endl;


    std::cout << "AddElements" << std::endl;
    gst_bin_add_many(GST_BIN(pipeline), filesrc, jpegdec, alpha, imagefreeze, waylandsink, NULL);

    std::cout << "Link Elements" << std::endl;
    gst_element_link_many (filesrc, jpegdec, imagefreeze, waylandsink, NULL);


    std::cout << "Set bus Message Watch" << std::endl;
    GstBus *bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    gst_bus_add_signal_watch(bus);


    std::cout << "Create gLoop" << std::endl;
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);


    std::cout << "Set Pipe Playing" << std::endl;
    gst_element_set_state(pipeline, GST_STATE_PLAYING);


    pipenloop pnl;
    pnl.p = pipeline;
    pnl.l = loop;

    g_signal_connect(bus, "message", G_CALLBACK(on_message), loop);	//Add EOS
    g_timeout_add(fpsIntervalMillis, (GSourceFunc) query_position, &pnl);     //Add Timer Callback

    std::cout << "Run main GLoop" << std::endl;
    g_main_loop_run(loop);


    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

	return 0;
}
