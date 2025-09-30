import { JSX } from 'react'
import AceEditor from 'react-ace'

import 'ace-builds/src-noconflict/mode-markdown'
import 'ace-builds/src-noconflict/theme-nord_dark'
import 'ace-builds/src-noconflict/ext-language_tools'

export default function CodeEditor({ documentContent, setDocumentContent }): JSX.Element {
  const onChange = (newValue: string): void => {
    setDocumentContent(newValue)
  }

  return (
    <>
      <AceEditor
        className="code-editor"
        mode="markdown"
        theme="nord_dark"
        onChange={onChange}
        value={documentContent}
        name="UNIQUE_ID_OF_DIV"
        editorProps={{ $blockScrolling: true }}
        fontSize={18}
        height="calc(100vh - 64px - 40px - 65px)"
        width="100%"
      />
    </>
  )
}
