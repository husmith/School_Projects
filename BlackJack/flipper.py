import tkinter as tk
from tkinter import *
from random import randint

root = tk.Tk()


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
        
    def display(self, side='back', num=0):
        """
        Change the label to show a new side of a card. If showing the
        front side the id parameter specifies which image (otherwise
        that parameter is ignored).
        """
        if side == 'back':
            self.configure(image=CardLabel.back_image)
        elif side == 'front':
            self.configure(image=CardLabel.images[num])
        else:
            self.configure(image=CardLabel.blank_image)
CardLabel.load_images()           
sides = ['front', 'blank', 'back']
move=0
i = 0

def flip():
    cards = [card1, card2, card3]
    global move, i
    if i%9 in range(3):
        move = 0
    if i%9 in range(3,6):
        move = 1
    if i%9 in range(6,9):
        move = 2
    label = cards[i%3]
    label.display(sides[move], randint(0,51))
    i+=1

card1 = CardLabel(root)
card1.grid(row=0, column=0, padx=10, pady=10)


card2 = CardLabel(root)
card2.grid(row=0, column=1,padx=10, pady=10)


card3 = CardLabel(root)
card3.grid(row=0, column=2,padx=10, pady=10)

button = Button(root, text='Flip!', command=flip)
button.grid(row=1, column=1)



    

root.mainloop()