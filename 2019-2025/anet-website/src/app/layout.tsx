import type { Metadata } from "next";
import { Geist, Geist_Mono } from "next/font/google";
import "./globals.css";
import "./waves.css";
import "./stars.css";


const geistSans = Geist({
  variable: "--font-geist-sans",
  subsets: ["latin"],
});

const geistMono = Geist_Mono({
  variable: "--font-geist-mono",
  subsets: ["latin"],
});

export const metadata: Metadata = {
  title: "J's desktop",
  description: "Personal homepage and digital workspace of Joey, IT Technician and Cloud Specialist.",
  keywords: [
    "Joey",
    "Asephri.net",
    "IT Technician",
    "Cloud Specialist",
    "Portfolio",
    "Personal Website",
    "Repair",
    "Hosting"
  ],
  authors: [{ name: "Joey" }],
  creator: "Joey",
  openGraph: {
    title: "J's desktop",
    description: "Personal homepage and digital workspace of Joey, IT Technician and Cloud Specialist.",
    url: "https://asephri.net/",
    siteName: "J's desktop",
    type: "website",
    locale: "en_US",
  },
  icons: {
    icon: "/favicon.ico",
  },
};


export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="en">
      <head>
        <link rel="icon" href="/favicon.ico" />
      </head>
      <body className={`${geistSans.variable} ${geistMono.variable} antialiased`}>
        {children}
        <div id="space">
          {Array.from({ length: 6 }).map((_, i) => (
            <div className="stars" key={i}></div>
          ))}
        </div>
        <div className="waves">
          <svg className="wave wave1" viewBox="0 0 1440 180" preserveAspectRatio="none">
            <defs>
              <linearGradient id="gradient1" x1="0" y1="0" x2="0" y2="1">
                <stop offset="60%" stopColor="#38bdf8" stopOpacity="0.6"/>
                <stop offset="100%" stopColor="#38bdf8" stopOpacity="0"/>
              </linearGradient>
            </defs>
            <path fill="url(#gradient1)" d="M0,80 C360,140 720,20 1080,80 1440,140 1440,140 1440,140 L1440,180 L0,180 Z"/>
          </svg>
          <svg className="wave wave2" viewBox="0 0 1440 180" preserveAspectRatio="none">
            <defs>
              <linearGradient id="gradient2" x1="0" y1="0" x2="0" y2="1">
                <stop offset="60%" stopColor="#818cf8" stopOpacity="0.4" />
                <stop offset="100%" stopColor="#818cf8" stopOpacity="0" />
              </linearGradient>
            </defs>
          <path fill="url(#gradient2)" d="M0,100 C360,50 720,150 1080,100 1440,50 1440,50 1440,50 L1440,180 L0,180 Z"/>
          </svg>
          <svg className="wave wave3" viewBox="0 0 1440 180" preserveAspectRatio="none">
            <defs>
              <linearGradient id="gradient3" x1="0" y1="0" x2="0" y2="1">
                <stop offset="60%" stopColor="#f472b6" stopOpacity="0.3" />
                <stop offset="100%" stopColor="#f472b6" stopOpacity="0" />
              </linearGradient>
            </defs>
          <path fill="url(#gradient3)" d="M0,90 C360,110 720,30 1080,90 1440,110 1440,110 1440,110 L1440,180 L0,180 Z"/>
        </svg>
        </div>
      </body>
    </html>
  );
}
