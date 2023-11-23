import sys

# Receive the argument from C

if len(sys.argv) != 2:
    print("Usage: python slave.py <input_string>")
    sys.exit(1)

search_string = sys.argv[1]
print(search_string)
search_string = "You have visited " + search_string

import tkinter as tk

val = 5  #no button click

def create_text_window(text):
    def go_back():
        global val 
        val = 11  # back
        window.destroy()  

    def go_fwd():
        global val 
        val = 22    #fwd
        window.destroy()

    def quit_code():
        global val
        val = 33    #quit
        window.destroy()

    window = tk.Tk()
    window.title("Internet Browser")
    window.geometry("1000x500")

    # Create a label to display the provided text
    label = tk.Label(window, text=text)
    label.pack()

    button_back = tk.Button(window, text="Back", command=go_back)
    button_back.pack()

    button_save_2 = tk.Button(window, text="Forward", command=go_fwd)
    button_save_2.pack()

    button_save_3= tk.Button(window, text="Exit", command=quit_code)
    button_save_3.pack()

    # Run the tkinter main loop
    window.mainloop()

# Example usage
sample_text = search_string
create_text_window(sample_text)

# Output the result when the window is closed
#print(val)
