# Project Title

Demo of Expandable and ExpandableP

## Intruduction

The only purpose is to demonstrate various ways that Expandable and ExpandableP may be used.  There are
three drop down command lists in the tool bar.  One each for the two separate stores and one for saving
each store.  The commands implement reading a file and loading into an Expandable(P) vector.  They
implement several ways to add each csv line to the expandable vector.  There are linear, binary searches
that are intended to find one specific entity in the vector.  There is also a regular expression search
implemented that will find all entries that match a reqular expression.  Finally the save drop down menu
will provide a way to save the entries in each store (expandable vector).

The implementation is inteded to demonstrate the code used to implement some features of Expandable(P).

The implementation of expandable allows the vector to grow as needed.  Expandable stores each entry in
the vector it self and therefore all the entries in the vector must be copied when it is expanded.
ExpandableP stores a pointer to each entry in the vector and it is the pointer that is copied.  The data
is stored in a heap node once.  There are some extra features in ExpandableP to allow for allocation and
deallocation.

## Getting Started

This version was created with Visual Studion 2022 (VS22).  It was compiled with the following properties:
  o Windows SDK Version: 10.0.xxxxx (latest)
  o Platfor Toolset: visual Studio 2022 (latest)
  o MFC: Use MFC in a Shared DLL
  o Character Set:  Use Unicode Character Set
  o Precompiled Header:  Not Using Precompiled Headers
  o Linker/Additional Dependencies:  Htmlhelp.lib

The HTML Help Workshop (HHW), Version 4.74.8702.0 (the last one produced) was used to prepare the help
file (WixApp.chm).  It is
copied into the Release directory.  I used Dreamweaver (DW) to do most of the content production of the
help files that the HTML Help Workshop produces (i.e. HHW is used to produce the pages/files needed
and DW is used to fill in the content).

Wix is used to create the &lt;AppName&gt;.msi file.  WixApp (one of my applications, see git) was used
to produce the product.wxs file.

Note:  In order to avoid hickups during the compilation/link process make sure the VS22 dependencies are
set so the projects are produced in the proper order.

## Prerequisites

Windows 7 or above.  visual Studio 2022 or above.  The WiX Toolset must be installed in Visual Studio.
The "HTML Help Workshop" (google it) must be installed on the PC.

### Installing

Execute the msi file to install the app.

## Update

### Update 2/16/24

Reorganized the Library so that it compiles once into Debug and Release directories under the Library
directory.

## Authors

Robert R. Van Tuyl

Contact:  romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

