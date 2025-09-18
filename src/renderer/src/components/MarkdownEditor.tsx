import { Crepe } from '@milkdown/crepe'
import { Milkdown, useEditor } from '@milkdown/react'
import { MilkdownProvider } from '@milkdown/react'
import { FC } from 'react'

import '@milkdown/crepe/theme/common/style.css'
import '@milkdown/crepe/theme/frame.css'

export const MarkdownEditorWrapper: FC = () => {
  useEditor((root) => {
    const crepe = new Crepe({
      root
    })
    return crepe
  }, [])

  return <Milkdown />
}

export const MarkdownEditor: FC = () => {
  return (
    <MilkdownProvider>
      <MarkdownEditorWrapper />
    </MilkdownProvider>
  )
}
