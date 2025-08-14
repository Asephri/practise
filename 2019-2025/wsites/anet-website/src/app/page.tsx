"use client";

import { useState } from "react";

import { Card, CardContent } from "@/components/ui/card";
import { Button } from "@/components/ui/button";
import { Sun, Moon } from "lucide-react";
import DraggableWindow from "./dragboxes";
import DecorativeBoat from "./decoration";

export default function HomePage() {
  const [darkMode, setDarkMode] = useState(true);
  const [windows, setWindows] = useState<
    { id: number; title: string; content: React.ReactNode }[]
  >([]);

  const openWindow = (title: string, content: React.ReactNode) => {
    setWindows((prev) => {
      if (prev.some((w) => w.title === title)) {
        return prev;
      }
      return [...prev, { id: Date.now(), title, content }];
    });
  };

  const closeWindow = (id: number) => {
    setWindows((prev) => prev.filter((w) => w.id !== id));
  };

  return (
    <div className={darkMode ? "dark bg-zinc-900 text-white min-h-screen flex flex-col" : "bg-white text-black min-h-screen flex flex-col"}>
      <header className="flex justify-between items-center w-full max-w-5xl mx-auto p-6">
        <h1 className="text-3xl font-bold">Asephri.net</h1>
        <Button variant="ghost" onClick={() => setDarkMode((d) => !d)}>
          {darkMode ? <Sun /> : <Moon />}
        </Button>
      </header>

      <main style={{ zIndex: 3 }} className="flex-grow flex justify-center items-center px-6">
        <Card className="rounded-2xl shadow-lg w-[60%] max-w-3xl">
          <CardContent className="p-6 flex flex-col items-center text-center">
            <h2 className="text-3xl font-extrabold mb-4">Hello!</h2>
            <div className="space-y-4 w-full">
              <p>
                <strong className="text-5xl text-blue-700 dark:text-blue-300">I'm Joseph</strong>
              </p>
              <p>
                <strong className="text-red-700 dark:text-red-300">IT Technician, Web design, Cloud hosting, Scripting.</strong>
              </p>
            </div>
            <nav aria-label="Main navigation" className="flex flex-wrap justify-center gap-3 mt-6 w-full">
              <Button onClick={() => openWindow("About",<><p>IT professional with over 6 years of experience in computer repair, network setup, and technical support in both employed and freelance roles.</p></>)}>About</Button>
              <Button onClick={() => openWindow("Work",<><p>Most of my work is available here @</p><a className="link" href="https://github.com/Asephri" target="_blank" rel="noopener noreferrer">GitHub</a></>)}>Work</Button>
              <Button onClick={() => openWindow("FAQ", <><p>Frequently asked questions:</p><br></br><p>Q1: Can you make/do this for me? A: Unless I get a reward, no.</p><p>Q2. Can you answer me right now and can i call you at out of work hours and pester you then get angry when you say no? A: no. go away.</p><p>Q3: What happened to the game servers and saves? A: I stopped hosting them. do it yourself.</p><p>Q4: Why aren't you on the group comms servers anymore. A: Very busy.</p></>)}>FAQ</Button>
              <Button onClick={() => openWindow("Contact", <p>you can email me here: joey@asephri.net</p>)}>Contact</Button>
            </nav>
          </CardContent>
        </Card>
      </main>

      {windows.map((win) => (
        <DraggableWindow
          key={win.id}
          title={win.title}
          content={win.content}
          onClose={() => closeWindow(win.id)}
        />
      ))}
      
      <DecorativeBoat/>

      <footer style={{ zIndex: 2}} className="text-center text-sm opacity-70 w-full max-w-5xl mx-auto p-6" role="contentinfo">
        © {new Date().getFullYear()} Asephri.net All rights reserved.
      </footer>
    </div>
  );
}
