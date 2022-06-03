import io
import webbrowser
import requests
from tkinter import *
from urllib.request import urlopen
from PIL import ImageTk, Image


class SamacharApp:

    def __init__(self):
        ## Fetch Data
        self.data = requests.get('https://newsapi.org/v2/top-headlines?country=in&apiKey=7809ae670d074143b50912e7032c2ed8').json()

        ## Initial GUI load
        self.load_gui()

        ## Load the 1st news items
        self.load_kabhar(0)

    def load_gui(self):
        self.root = Tk()
        self.root.geometry('350x600')
        self.root.resizable(0, 0)
        self.root.title('Apani Kabhar App')
        self.root.configure(background='light green')

    def clear(self):
        for i in self.root.pack_slaves():
            i.destroy()

    def load_kabhar(self, index):
        ## Clear the screen for the new samachar items
        self.clear()

        ### Image
        try:
            img_url = self.data['articles'][index]['urlToImage']
            raw_data = urlopen(img_url).read()
            im = Image.open(io.BytesIO(raw_data)).resize((350, 250))
            photo = ImageTk.PhotoImage(im)
        except:
            img_url = 'https://static.wikia.nocookie.net/6d37f599-6b4a-4053-b2f3-be1bb11109ce/scale-to-width/755'
            raw_data = urlopen(img_url).read()
            im = Image.open(io.BytesIO(raw_data)).resize((350, 250))
            photo = ImageTk.PhotoImage(im)

        label = Label(self.root, image=photo)
        label.pack()

        heading = Label(self.root, text=self.data['articles'][index]['title'], bg='maroon', fg='orange',
                        wraplength=350,
                        justify='center')
        heading.pack(pady=(10, 20))
        heading.config(font=('verdana', 15))

        details = Label(self.root, text=self.data['articles'][index]['description'], bg='maroon', fg='orange',
                        wraplength=350,
                        justify='center')
        details.pack(pady=(2, 20))
        details.config(font=('verdana', 12))

        frame = Frame(self.root, bg='green')
        frame.pack(expand=True, fill=BOTH)

        if index != 0:
            prev = Button(frame, text='Prev', width=16, height=16, command=lambda:self.load_kabhar(index-1))
            prev.pack(side=LEFT)

        read = Button(frame, text='Read More', width=16, height=16, command=lambda:self.open_link(self.data['articles'][index]['url']))
        read.pack(side=LEFT)

        if index != len(self.data['articles'])-1:
            nxt = Button(frame, text='Next', width=16, height=16, command=lambda:self.load_kabhar(index+1))
            nxt.pack(side=LEFT)

        self.root.mainloop()

    def open_link(self, url):
        webbrowser.open(url)

obj = SamacharApp()
