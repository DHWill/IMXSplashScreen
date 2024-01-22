gst-launch-1.0 filesrc location=PXL_20240116_150403266.jpg ! jpegdec ! videoconvert ! imagefreeze num-buffers=200 ! waylandsink window-width=2160 window-height=3840
