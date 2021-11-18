# Expandable(P) Test Application

Just a simple windows application with 4 drop down tool bar menus to test both a class (i.e. Store)
containing an Expandable vector and a class (i.e. StoreP) containing an ExpandableP vector.  The tests
of each Expanable vector are:

  - Load vector from a file by appending each new line to the end of the vector
  - Load vector from a file by inserting each new line into the vector such that the vector is sorted by
by a key (note:  The key's are created differently for the two vector types, see code for details).
  - Find an element in the vector by using a linear search
  - Find an element in the vector by using a binary search (only works in a sorted array)
  - Insert an element in the vector and then delete it.
  - Sort the vector using a qsort function template

After each test the results are displayed.  A test sequence starts with a load (unsorted or sorted)
followed by one or more of the remaning tests.  After each test the entire vector is displayed so that the
effect of the test may be observed.  The only time the display is cleared is before the load so that one
can compare the initial load with the effect of the tests.

## Getting Started

This version was created with Visual Studion 2017.  It was compiled with the following properties:
  o Windows SDK Version: 10.0.18362.0
  o Platfor Toolset: visual Studio 2017 (v141)
  o MFC: Use MFC in a Shared DLL
  o Character Set:  Use Unicode Character Set

The HTML Help Workshop (HHW), Version 4.74.8702.0 was used to prepare the help file (WixApp.chm).  It is
copied into the Release directory.  I used Dreamweaver (DW) to do most of the content production of the
help files that the HTML Help Workshop produces (i.e. HHW is used to produce the pages/files needed
and DW is used to fill in the content).

The Extension "Wix Toolset visual Studio 2017 Extension" is also required.  It can be found in
"visual Studio 2017/Tools/Extensions and Updates".

Changes to the Installer may made by editing the "Product.wxs" file or obtaining the WixApp on Git.

### Prerequisites

The WiX Toolset must be installed in Visual Studio.  The "HTML Help Workshop" (google it) must be
installed.  Visual Studio 2017 or later.

### Installing

Not really necessary as the test may be run from the Debug or Release directory.  Only the Release version
is included in the Git Upload.

## Running the tests

Start the app.  there are four toolbar drop down menu visible on the toolbar:

  - Load StoreP
  - Load StoreP Sorted
  - Load Store
  - Load Store Sorted

The test sequence starts with selecting a Load command.  The click on the little triangle to the right
of the button and click on one of the test commands.  The results of the load and test command should
appear in the window.  Examine the window (scrolling as necessary) to determine if the result looks
correct.

One of the critical tests is to run many tests and then exit the program.  If this is done in the debugger
in the debug version any lost memory blocks will be listed.  There should be no lost memory blocks as
in Windows they cannot be recoved by exiting an application.

## Authors

Robert R. Van Tuyl

Contact:  romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details


