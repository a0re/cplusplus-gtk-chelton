# Required Packages
```
sudo pacman -S libsigc++-3.0 libsigc++ gtk4 glibmm pangomm cairomm pkg-config glib2 pango cairo gtkmm-4.0 graphene cmake make
```

Will work with Clion, just need to refresh CMakeLists.txt each time you add a file, or you can just remove the glob recursive from CMakeLists and have CLion add them in manually for you. This is annoying tbh, should just recognize that it's globbing.

# GIGACHADS ONLY:
Just use vim and run the program with ./make_run.sh :)
