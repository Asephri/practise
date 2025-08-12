"use client";

import { useState, useEffect } from "react";

export default function DecorativeBoat() {
  const [isDesktop, setIsDesktop] = useState(false);

  useEffect(() => {
    function onResize() {
      setIsDesktop(window.innerWidth >= 1025);
    }

    onResize();
    window.addEventListener("resize", onResize);
    return () => window.removeEventListener("resize", onResize);
  }, []);

  if (!isDesktop) return null;

  return (
    <div
      style={{ position: "fixed", bottom: 40, left: 25, zIndex: 50, pointerEvents: "none" }}
      aria-hidden="true"
    >
      <img
        src="orang.png"
        alt="Decorative boat"
        style={{ width: 400, height: "auto", pointerEvents: "auto" }}
        className="sway"
      />
    </div>
  );
}