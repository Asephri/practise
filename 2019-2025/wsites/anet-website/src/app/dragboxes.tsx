"use client";

import { useState, useRef, useEffect, useCallback } from "react";

interface DraggableWindowProps {
  title: string;
  content: React.ReactNode;
  onClose: () => void;
  index?: number;
}

export default function DraggableWindow({
  title,
  content,
  onClose,
  index = 0,
}: DraggableWindowProps) {
  const [pos, setPos] = useState({ x: 0, y: 0 });
  const draggingRef = useRef(false);
  const offsetRef = useRef({ x: 0, y: 0 });
  const windowRef = useRef<HTMLDivElement>(null);

  // Center window based on its actual size
  useEffect(() => {
    if (!windowRef.current) return;

    const { width, height } = windowRef.current.getBoundingClientRect();
    const centerX = (window.innerWidth - width) / 2;
    const centerY = (window.innerHeight - height) / 2 + index * 30;

    setPos({ x: centerX, y: centerY });
  }, [content, index]);

  // Mouse move and up handlers
  const handleMouseMove = useCallback((e: MouseEvent) => {
    if (!draggingRef.current) return;
    setPos({ x: e.clientX - offsetRef.current.x, y: e.clientY - offsetRef.current.y });
  }, []);

  const handleMouseUp = useCallback(() => {
    draggingRef.current = false;
  }, []);

  useEffect(() => {
    window.addEventListener("mousemove", handleMouseMove);
    window.addEventListener("mouseup", handleMouseUp);
    return () => {
      window.removeEventListener("mousemove", handleMouseMove);
      window.removeEventListener("mouseup", handleMouseUp);
    };
  }, [handleMouseMove, handleMouseUp]);

  // On drag start
  const handleMouseDown = (e: React.MouseEvent) => {
    draggingRef.current = true;
    offsetRef.current = { x: e.clientX - pos.x, y: e.clientY - pos.y };
  };

  return (
    <div
      ref={windowRef}
      className="fixed bg-white dark:bg-zinc-800 shadow-lg border"
      style={{
        top: pos.y,
        left: pos.x,
        zIndex: 100 + index,
        minWidth: 250,
      }}
    >
      <div
        className="flex justify-between items-center px-3 py-2 cursor-move bg-zinc-200 dark:bg-zinc-700"
        onMouseDown={handleMouseDown}
      >
        <span className="font-bold">{title}</span>
        <button onClick={onClose} className="px-2" aria-label="Close window">
          ✕
        </button>
      </div>
      <div className="p-3">{content}</div>
    </div>
  );
}
