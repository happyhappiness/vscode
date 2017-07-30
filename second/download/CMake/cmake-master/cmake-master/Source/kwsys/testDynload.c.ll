; ModuleID = '/data/download/cmake/cmake-master/Source/kwsys/testDynload.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@TestDynamicLoaderData = global i32 0, align 4

; Function Attrs: nounwind uwtable
define void @TestDynamicLoaderSymbolPointer() #0 !dbg !4 {
entry:
  ret void, !dbg !13
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!10, !11}
!llvm.ident = !{!12}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3, globals: !7)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Source/kwsys/testDynload.c", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "TestDynamicLoaderSymbolPointer", scope: !1, file: !1, line: 11, type: !5, isLocal: false, isDefinition: true, scopeLine: 12, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{null}
!7 = !{!8}
!8 = !DIGlobalVariable(name: "TestDynamicLoaderData", scope: !0, file: !1, line: 9, type: !9, isLocal: false, isDefinition: true, variable: i32* @TestDynamicLoaderData)
!9 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!10 = !{i32 2, !"Dwarf Version", i32 4}
!11 = !{i32 2, !"Debug Info Version", i32 3}
!12 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!13 = !DILocation(line: 13, column: 1, scope: !4)
