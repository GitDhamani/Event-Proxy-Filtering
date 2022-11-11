# Event-Proxy-Filtering
Implementing Event Filtering in QT and C++.

Here I am making use of the Proxy Filter functionality provided by QT. This is when we load an object to front-run, or intercept events originally intended for the event handler on another class. This way we can filter and trap the events which are important to us and let the unimportant ones through. In this case we are loading a List View Widget with a list of system colour names that when clicked on, fill the adjacent label with that colour.

The Filtering comes into play when you start typing in your colour choices into the edit box at the bottom. As you type text it will apply this to the filter object as a Regular Expression. This means rather than all colours being populated in the List View widget, we are intercepting all of the colours intended for it except those matching the Regular expression.

The result is as you type the colour you're looking for, the List View updates itself to show you any colour names which match this string.

https://user-images.githubusercontent.com/111576658/201360337-5822ff82-6af2-401b-bc17-5ba496d1a432.mp4

