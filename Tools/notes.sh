gst-launch-1.0 filesrc location=Flower/231214_FP_Active_short_cloth_ring_petals_updated_cross_fades-2x-RIFE-RIFE4.6-60fps.mp4 ! qtdemux ! h264parse ! v4l2h264dec ! imxvideoconvert_g2d ! queue ! waylandsink window-width=1920 window-height=1920

