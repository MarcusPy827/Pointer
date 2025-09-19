import { Crepe } from '@milkdown/crepe'
import { Milkdown, useEditor } from '@milkdown/react'
import { MilkdownProvider } from '@milkdown/react'
import { listener, listenerCtx } from '@milkdown/plugin-listener'
import { JSX } from 'react'

import '@milkdown/crepe/theme/common/style.css'
import '@milkdown/crepe/theme/frame.css'

export function MarkdownEditorWrapper({ documentContent, setDocumentContent }): JSX.Element {
  useEditor((root) => {
    const crepe = new Crepe({
      root,
      defaultValue: documentContent,
      features: {
        [Crepe.Feature.Toolbar]: true,
        [Crepe.Feature.Latex]: true
      }
    })

    crepe.editor.config((ctx) => {
      const listener = ctx.get(listenerCtx)
      listener.markdownUpdated((_, markdown, prevMarkdown) => {
        console.log('Markdown updated:', markdown)
        setDocumentContent(markdown)
      })
    })
    return crepe
  }, [])

  return <Milkdown />
}

export default function MarkdownEditor({ documentContent, setDocumentContent }): JSX.Element {
  return (
    <MilkdownProvider>
      <MarkdownEditorWrapper
        documentContent={documentContent}
        setDocumentContent={setDocumentContent}
      />
    </MilkdownProvider>
  )
}
