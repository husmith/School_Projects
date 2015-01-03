from tkinter import *
from random import randint

class CardLabel(Label):
    """
    Demonstrating how to specialize the Label class to make a specific
    type of label for an application to use
    """
    
    def __init__(self, parent):
        "The default image for a new label is the back of a card"
        Label.__init__(self, parent, image=CardLabel.back_image)
        
    @staticmethod
    def load_images():
        "Get the card images from files, save them in a list (a class variable)"
        CardLabel.images = [PhotoImage(file="card-images/card{}.gif".format(i)) for i in range(52)]
        CardLabel.back_image = PhotoImage(file="card-images/back-blue.gif")
        CardLabel.blank_image = PhotoImage(file="card-images/blank.gif")
        
    def display(self, side='back', id=0):
        """
        Change the label to show a new side of a card. If showing the
        front side the id parameter specifies which image (otherwise
        that parameter is ignored).
        """
        if side == 'back':
            self.configure(image=CardLabel.back_image)
        elif side == 'front':
            self.configure(image=CardLabel.images[id])
        else:
            self.configure(image=CardLabel.blank_image)
            
# Code snippet -- how to initialize the class:

#     CardLabel.load_images()

# Code snippet -- how to use the display method:

#     sides = ['front', 'blank', 'back']
#     move = 0
#         
#     def flip():
#         move = (move + 1) % 3
#         label.display(sides[move], randint(0,51))
