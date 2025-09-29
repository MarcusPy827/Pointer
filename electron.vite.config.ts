import { resolve } from 'path'
import { defineConfig, externalizeDepsPlugin } from 'electron-vite'
import react from '@vitejs/plugin-react'
import { viteStaticCopy } from 'vite-plugin-static-copy'
import { createRequire } from 'node:module'
import path from 'node:path'

const require = createRequire(import.meta.url)
const monacoPkg = require.resolve('monaco-editor/package.json')
const monacoVsDir = path.join(path.dirname(monacoPkg), 'min', 'vs')

export default defineConfig({
  main: {
    plugins: [externalizeDepsPlugin()]
  },
  preload: {
    plugins: [externalizeDepsPlugin()]
  },
  renderer: {
    base: './',
    resolve: {
      alias: {
        '@renderer': resolve('src/renderer/src')
      }
    },
    plugins: [
      react(),
      viteStaticCopy({
        targets: [
          {
            src: `${monacoVsDir}/**/*`,
            dest: 'monaco/vs'
          }
        ]
      })
    ]
  }
})
