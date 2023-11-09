# TextArtLinkedList
This program is an interactive ASCII art editor that allows users to create, edit, save, and load text-based art. It provides various functionalities like editing the art, moving elements, replacing characters, clearing the canvas, and offering animation features. The program operates through a menu system where users can input commands to perform specific actions on the displayed ASCII canvas. Some of the functionalities include:

- **Edit Canvas**: Allows users to directly modify the displayed ASCII art.
- **Move Canvas**: Shifts the entire art in horizontal and vertical directions.
- **Replace Characters**: Substitutes specific characters with others in the art.
- **Clear Canvas**: Resets the entire canvas, setting all characters to spaces.
- **Save and Load**: Enables users to save and load their ASCII art to/from files.
- **Undo and Redo**: Provides the ability to undo and redo recent actions on the art.
- **Clipping and Animation**: Supports a clipboard feature to copy parts of the art and an animation mode.
- **History Tracking**: The linked list maintains a sequence of canvas states, recording each change made to the ASCII art.
- **Undo and Redo Functionality**: Enables users to move backward and forward in the canvas's editing history, allowing for reverting to previous states or redoing undone changes.
- **Efficient State Management**: Offers a structured approach for inserting, removing, and navigating through different versions of the canvas without duplicating the entire canvas data.

The program's functionalities are controlled through a command-line interface, where users input specific commands to trigger actions on the displayed text-based art canvas. It utilizes various functions such as displaying the canvas, navigating the cursor within the canvas, and handling input for editing and modifying the ASCII art.
