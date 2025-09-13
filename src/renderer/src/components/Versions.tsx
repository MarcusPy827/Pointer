import { useState } from 'react'

export function getAppVersionString(): string {
  return '1.0.0'
}

function Versions(): React.JSX.Element {
  // @ts-ignore Field defined by electron
  const [versions] = useState(window.electron.process.versions)

  return (
    <ul className="versions">
      <li className="electron-version">Electron v{versions.electron}</li>
      <li className="chrome-version">Chromium v{versions.chrome}</li>
      <li className="node-version">Node v{versions.node}</li>
    </ul>
  )
}

export default Versions
